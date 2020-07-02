#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/loglevel.h"
#include "log4cplus/loggingmacros.h"

#include <iostream>
using namespace std;
using namespace log4cplus;


//#define LOG4CPLUS_DISABLE_FATAL
//#define LOG4CPLUS_DISABLE_WARN


int main()
{
	SharedAppenderPtr _append(new ConsoleAppender());
	_append->setName("test");
	Logger::getRoot().addAppender(_append);
	Logger root = Logger::getRoot();
	Logger test = Logger::getInstance("test");

	Logger subTest = Logger::getInstance("test.subtest");
	LogLevelManager& llm = getLogLevelManager();
	cout << endl << "Before Setting, Default LogLevel" << endl;
	LOG4CPLUS_FATAL(root, "root: " << llm.toString(root.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test: " << llm.toString(test.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test.subtest:" << llm.toString(subTest.getChainedLogLevel()));
	cout << endl << "Setting test.subtest to WARN" << endl;
	subTest.setLogLevel(WARN_LOG_LEVEL);
	LOG4CPLUS_FATAL(root, "root: " << llm.toString(root.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test: " << llm.toString(test.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test.subtest: " << llm.toString(subTest.getChainedLogLevel()));

	LOG4CPLUS_WARN(subTest, "test.subtest   ceshi  ");

	cout << endl << "Setting test to TRACE" << endl;
	test.setLogLevel(TRACE_LOG_LEVEL);
	LOG4CPLUS_FATAL(root, "root: " << llm.toString(root.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test: " << llm.toString(test.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test.subtest: " << llm.toString(subTest.getChainedLogLevel()));
	cout << endl << "Setting test.subtest to NO_LEVEL" << endl;
	subTest.setLogLevel(NOT_SET_LOG_LEVEL);
	LOG4CPLUS_FATAL(root, "root: " << llm.toString(root.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test: " << llm.toString(test.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test.subtest: " << llm.toString(subTest.getChainedLogLevel()) << '\n');
	cout << "create a logger test_bak, named \"test_\", too. " << endl;
	Logger test_bak = Logger::getInstance("test");
	cout << "Setting test to INFO, so test_bak also be set to INFO" << endl;
	test.setLogLevel(INFO_LOG_LEVEL);
	LOG4CPLUS_FATAL(root, "test: " << llm.toString(test.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test_bak: " << llm.toString(test_bak.getChainedLogLevel()));
	return 0;
}