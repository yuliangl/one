#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <sstream>
#include <fstream>
#include <time.h>
#include <vector>
#include <list>
#include <map>
#include <stdarg.h>


namespace sylar {

#define partprintf(name, level, fmt, ...) \
    if(LoggerMgr::getInstance()->getLoggers().find(name) != LoggerMgr::getInstance()->getLoggers().end()){ \
        LoggerMgr::getInstance()->getLoggers()[name]->log(level, __FILE__, __LINE__, fmt, __VA_ARGS__); \
    }

#define printf_debug(name, fmt, ...) partprintf(name, LogLevel::DEBUG, fmt, __VA_ARGS__)
#define printf_info(name, fmt, ...) partprintf(name, LogLevel::INFO, fmt, __VA_ARGS__)
#define printf_error(name, fmt, ...) partprintf(name, LogLevel::ERROR, fmt, __VA_ARGS__)
#define printf_fatal(name, fmt, ...) partprintf(name, LogLevel::FATAL, fmt, __VA_ARGS__)


class LogLevel {
public:
    enum level {
        UNKOWN = 0,
        DEBUG = 1,
        INFO = 2,
        ERROR = 3,
        FATAL = 4
    };
    static const std::string toString[5];
};

class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();
    LogEvent(const char* file, uint32_t line, uint32_t elapse, 
                uint32_t threadId, uint32_t fiberId, uint64_t time, std::string threadName);
    ~LogEvent();

    const char* getFile() const { return m_file; }
    const uint32_t getLine() const { return m_line; }
    const uint32_t getElapse() const { return m_elapse; }
    const uint32_t getThreadId() const { return m_threadId; }
    const uint32_t getFiberId() const { return m_fiberId; }
    const uint64_t getTime() const { return m_time; }
    const std::string getThreadName() const { return m_threadName;}
    const LogLevel::level getLevel() const { return m_level;}
    const std::string getLogName() const { return m_logName;}
    std::stringstream& getSS() { return m_ss; }
    const std::string getContent() const { return m_ss.str(); }

    void setLevel(LogLevel::level level) { m_level = level;}
    void setLogName(std::string logName) { m_logName = logName;}
    void setFile(const char* file) { m_file = file;}
    void setLine(uint32_t line) { m_line = line;}
private:
    const char* m_file = nullptr;
    uint32_t m_line = 0;
    uint32_t m_elapse = 0;
    uint32_t m_threadId = 0;
    uint32_t m_fiberId = 0;
    uint64_t m_time = 0;
    std::string m_threadName;
    LogLevel::level m_level;
    std::string m_logName;
    std::stringstream m_ss;
};


class LogFormatItem {
public:
    typedef std::shared_ptr<LogFormatItem> ptr;
    LogFormatItem();
    virtual ~LogFormatItem();

    virtual void itemout(std::ostream& os, LogEvent::ptr event) = 0;

private:
};


class MessageFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << event->getContent();
    }
};

class LevelFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << LogLevel::toString[event->getLevel()];
    }
};

class ElapseFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << event->getElapse();
    }
};

class NameLogFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << event->getLogName();
    }
};

class ThreadIdFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << event->getThreadId();
    }
};

class FiberIdFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << event->getFiberId();
    }
};

class ThreadNameFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << event->getThreadName();
    }
};

class DateTimeFormatItem : public LogFormatItem {
public:
    DateTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%S")
        :m_format(format) {
        if(m_format.empty()) {
            m_format = "%Y-%m-%d %H:%M:%S";
        }
    }

    void itemout(std::ostream& os, LogEvent::ptr event) override {
        struct tm tm;
        time_t time = event->getTime();
        localtime_r(&time, &tm);
        char buf[64];
        strftime(buf, sizeof(buf), m_format.c_str(), &tm);
        os << buf;
    }
private:
    std::string m_format;
};

class FilenameFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << event->getFile();
    }
};

class LineFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << event->getLine();
    }
};

class NewLineFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << std::endl;
    }
};

class TabFormatItem : public LogFormatItem {
public:
    void itemout(std::ostream& os, LogEvent::ptr event) override {
        os << "\t";
    }
};


class LogFormat{
public:
    typedef std::shared_ptr<LogFormat> ptr;
    LogFormat(std::string pattern);
    ~LogFormat();

    void init();
    void foutItem(std::ostream& os, LogEvent::ptr event);

private:
    std::string m_pattern;
    std::vector<LogFormatItem::ptr> m_items;

};


class LogAppender {
public:
    typedef std::shared_ptr<LogAppender> ptr;
    LogAppender();
    virtual ~LogAppender();
    
    virtual void apout(LogEvent::ptr event, LogFormat::ptr format) = 0;
private:
};

class StdLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdLogAppender> ptr;
    StdLogAppender();
    ~StdLogAppender();

    void apout(LogEvent::ptr event, LogFormat::ptr format) override;
private:
};

class FileLogAppender : public LogAppender {
public: 
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);
    ~FileLogAppender();

    void apout(LogEvent::ptr event, LogFormat::ptr format) override;
private:
    std::string m_filename;
    std::ofstream m_fstream;

};
class Logger {
public:
    typedef std::shared_ptr<Logger> ptr;
    Logger();
    Logger(std::string name, LogLevel::level level, LogEvent::ptr event, LogFormat::ptr format, LogAppender::ptr appender);
    ~Logger();

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);

    void log(LogLevel::level level, std::string context);
    void log(LogLevel::level level, const char* file, uint32_t line, const char* fmt, ...);
    void format(const char* fmt, va_list al);
    void flushContext() {
        m_event->getSS().str("");
        m_event->getSS().clear();
    }

    std::string getName() const {return m_name;}
    LogLevel::level getLevel() const {return m_level;}
private:
    std::string m_name;
    LogLevel::level m_level;
    LogEvent::ptr m_event;
    LogFormat::ptr m_format;
    std::list<LogAppender::ptr> m_appenders;


};


class LoggerMgr {
public:
    LoggerMgr();
    ~LoggerMgr();

    static LoggerMgr* getInstance();
    void init();
    void addLogger(Logger::ptr logger);
    void log(const std::string& name, LogLevel::level level, std::string msg);

    std::map<std::string, Logger::ptr>& getLoggers() {return m_loggers;}
private:
    static LoggerMgr* s_instancePtr;
    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;



};

}//end

#endif


























