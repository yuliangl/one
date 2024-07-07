#include <iostream>


#include "log.h"

namespace sylar{


const std::string LogLevel::toString[5] = {
    "UNKOWN",
    "DEBUG",
    "INFO",
    "ERROR",
    "FATAL"
};


LogEvent::LogEvent(){
}
LogEvent::LogEvent(const char* file, uint32_t line, uint32_t elapse, 
                uint32_t threadId, uint32_t fiberId, uint64_t time, std::string threadName)
    :m_file(file)
    ,m_line(line)
    ,m_elapse(elapse)
    ,m_threadId(threadId)
    ,m_fiberId(fiberId)
    ,m_time(time)
    ,m_threadName(threadName)
{
}
    
LogEvent::~LogEvent(){
}

LogFormatItem::LogFormatItem(){
}
LogFormatItem::~LogFormatItem(){
}

LogFormat::LogFormat(std::string pattern)
    :m_pattern(pattern)
{
    init();
}    

LogFormat::~LogFormat(){
}

void LogFormat::init(){
    std::map<char, LogFormatItem::ptr> itemMap = {
        {'m', LogFormatItem::ptr(new MessageFormatItem() )},
        {'p', LogFormatItem::ptr(new LevelFormatItem() )},
        {'r', LogFormatItem::ptr(new ElapseFormatItem() )},
        {'c', LogFormatItem::ptr(new NameLogFormatItem() )},
        {'t', LogFormatItem::ptr(new ThreadIdFormatItem() )},
        {'n', LogFormatItem::ptr(new NewLineFormatItem() )},
        {'d', LogFormatItem::ptr(new DateTimeFormatItem() )},
        {'f', LogFormatItem::ptr(new FilenameFormatItem() )},
        {'l', LogFormatItem::ptr(new LineFormatItem() )},
        {'T', LogFormatItem::ptr(new TabFormatItem() )},
        {'F', LogFormatItem::ptr(new FiberIdFormatItem() )},
        {'N', LogFormatItem::ptr(new ThreadNameFormatItem() )}
    };

    for(auto& it : m_pattern){
        if(it != '%')
            m_items.push_back(itemMap.at(it)); 
    }
#if 0
    for(auto& it : m_pattern){
       for(auto itmap=itemMap.begin(); itmap != itemMap.end(); ++it ){
           if(it == itmap->first()){
               m_items.push_back(itmap->second());
           }
       }
    }
#endif
}

void LogFormat::foutItem(std::ostream& os, LogEvent::ptr event){
    for(auto& item : m_items){
        item->itemout(os, event);
    }
}

LogAppender::LogAppender(){
}
LogAppender::~LogAppender(){
}
StdLogAppender::StdLogAppender(){
}
StdLogAppender::~StdLogAppender(){
}

void StdLogAppender::apout(LogEvent::ptr event, LogFormat::ptr format){
    format->foutItem(std::cout, event);

}

FileLogAppender::FileLogAppender(const std::string& filename)
    :m_filename(filename)
{
    if(m_fstream.is_open()){
        m_fstream.close();
    }
    m_fstream.open(m_filename);
}

FileLogAppender::~FileLogAppender(){
    if(m_fstream.is_open()){
        m_fstream.close();
    }
}

void FileLogAppender::apout(LogEvent::ptr event, LogFormat::ptr format){
    format->foutItem(m_fstream, event);
}

Logger::Logger(){
}

Logger::Logger(std::string name, LogLevel::level level, LogEvent::ptr event, LogFormat::ptr format, LogAppender::ptr appender)
    :m_name(name)
    ,m_level(level)
    ,m_event(event)
    ,m_format(format)
{
    addAppender(appender);
    m_event->setLevel(m_level);
    m_event->setLogName(m_name);
}

Logger::~Logger(){
}

void Logger::addAppender(LogAppender::ptr appender){
    m_appenders.push_back(appender);
}
void Logger::delAppender(LogAppender::ptr appender){
    for(auto it=m_appenders.begin(); it != m_appenders.end(); ++it){
        if(*it == appender){
            m_appenders.erase(it);
        }
    }

}

void Logger::log(LogLevel::level level, std::string context){
    if(m_level > level)
        return;
    
    m_event->getSS() << context;
    for(auto& appender : m_appenders){
        appender->apout(m_event, m_format);
    }

    this->flushContext();
}

void Logger::log(LogLevel::level level, const char* file, uint32_t line, const char* fmt, ...){
    if(m_level > level)
        return;

    m_event->setFile(file);
    m_event->setLine(line);
    va_list al;
    va_start(al,fmt);
    this->format(fmt, al);
    va_end(al);

    for(auto& appender : m_appenders){
        appender->apout(m_event, m_format);
    }

    this->flushContext();
}
void Logger::format(const char* fmt, va_list al){
    char* buf = nullptr;
    int len = vasprintf(&buf, fmt, al);
    if(len != -1) {
        m_event->getSS() << std::string(buf, len);
        free(buf);
    }
}

LoggerMgr::LoggerMgr(){
}

LoggerMgr::~LoggerMgr(){
}
LoggerMgr* LoggerMgr::s_instancePtr = nullptr;
LoggerMgr* LoggerMgr::getInstance(){
    if(s_instancePtr == nullptr){
        s_instancePtr = new LoggerMgr;
    }
    return s_instancePtr;
}

void LoggerMgr::init(){
    std::cout << "enter main function." << std::endl;
    LogEvent::ptr eventPtr( new LogEvent(__FILE__, __LINE__, 0, 0, 0, 1, "main"));
    std::cout << "create LogEvent finish." << std::endl;

    LogFormat::ptr formatPtr(new LogFormat("%d%T%c%T%t%T%p%T%f%T%l%T%m%n"));
    std::cout << "create LogFormat finish." << std::endl;

    LogAppender::ptr appenderPtr(new StdLogAppender());
    std::cout << "create LogAppender finish." << std::endl;

    LogAppender::ptr fileAppenderPtr(new FileLogAppender("../log.txt"));
    std::cout << "create FileLogAppender finish." << std::endl;
    
    m_root = Logger::ptr(new Logger("ROOT", LogLevel::DEBUG, eventPtr, formatPtr, appenderPtr));
    m_root->addAppender(fileAppenderPtr);
    std::cout << "create Logger finish." << std::endl;

    m_loggers.insert({m_root->getName(), m_root});

}

void LoggerMgr::addLogger(Logger::ptr logger){
    m_loggers[logger->getName()] = logger;
}

void LoggerMgr::log(const std::string& name, LogLevel::level level, std::string msg){
    if(m_loggers.find(name) != m_loggers.end()){
        m_loggers[name]->log(level, msg);
    }
}

    
}// namespace sylar


























