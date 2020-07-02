/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include <sys/types.h>
#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>
#include <fstream>
#include "Parser.h"

using namespace std;

Parser::Parser(const std::string request)
{
    assert(request.size() > 0);
    this->_request = request;
}

std::string Parser::sendErrorMsg(const std::string &errorNum,const std::string &shortMsg,const std::string &longMsg)
{
	
	std::string msg = "HTTP/1.0 " + errorNum + " " + shortMsg + "\r\n";
	msg += "Server: Tiny Web Server\r\n";
	
	std::string content;
	content += "<html>\r\n<head><title>Error</title></head>\r\n";
	content += "<body bgcolor=""ffffff"">test</body>\r\n";
	content += "</html>\r\n";

	char tmp[32]={0};
	sprintf(tmp,"%d",content.length());
	msg += "Content-length: " + std::string(tmp) + "\r\n";
	msg += "Content-type: text/html\r\n\n";
	msg+=content;

	printf("Parser::sendErrorMsg  longmsg:%s  len:%d \n",longMsg.c_str(),content.length());

	ofstream fout("./home3.html");
	fout << msg; // fout用法和cout一致, 不过是写到文件里面去
	return msg;
}



void Parser::parseURI()
{
	_fileName = ".";
	if(_parseResult.uri == "/")
		_fileName += "/home.html";
}


void Parser::getFileType()
{
	const char *name = _fileName.c_str();
	if(strstr(name, ".html"))
		_fileType = "text/html";
	else if(strstr(name, ".pdf"))
		_fileType = "application/pdf";
	else if(strstr(name, ".png"))
		_fileType = "image/png";
	else if(strstr(name, ".gif"))
		_fileType = "image/gif";
	else if(strstr(name, ".jpg"))
		_fileType = "image/jpg";
	else if(strstr(name, ".jpeg"))
		_fileType = "image/jpeg";
	else if(strstr(name, ".css"))
		_fileType = "test/css";
	else
		_fileType = "text/plain";
}

std::string Parser::getParseResult()
{
	std::string strResult;

    parseLine();
    parseRequestLine();
    parseHeaders();	
	//printf("connection:%s  host:%s   method:%s  uri:%s   version:%s \n",_parseResult.connection.c_str()
		//,_parseResult.host.c_str(),_parseResult.method.c_str(),_parseResult.uri.c_str(),_parseResult.version.c_str());
	std::cout<<"_request.method :"<<_parseResult.method.c_str()<<std::endl;
	if(_parseResult.method != "GET")
	{
		return sendErrorMsg("501", "Not Implemented","Server doesn't implement this method");
	}
	parseURI();
	struct stat fileInfo;
	if(stat(_fileName.c_str(), &fileInfo) < 0)
	{
		std::cout << "404 Not found: Server couldn't find this file." << std::endl;
		return sendErrorMsg("404", "Not Found", "Server couldn't find this file");
	}
	if(!(S_ISREG(fileInfo.st_mode)) || !(S_IRUSR & fileInfo.st_mode))
	{
		
		////return sendErrorMsg("403", "Forbidden", "Server couldn't read this file");
		//_fileName="./home2.html";
		//stat(_fileName.c_str(), &fileInfo);
		//getFileType();
		//std::string msg = "HTTP/1.1 200 OK\r\n";
		//msg += "Server: Tiny Web Server\r\n";
		//char tmp[32]={0};
		//sprintf(tmp,"%d",fileInfo.st_size);
		//msg += "Content-length: " + std::string(tmp) + "\r\n";
		//msg += "Content-type: " + _fileType + "\r\n\r\n";
		//int fd = open("./home2.html", O_RDONLY, 0);

		//char extrabuf[65535];
		//char *ptr = extrabuf;
		//int nleft = 65535;
		//int nread;
		//while((nread = read(fd, ptr, nleft)) < 0)
		//{
		//	if(errno == EINTR)
		//		nread = 0;
		//	else 
		//	{
		//		std::cout << "403 Forbidden: Server couldn't read this file." << std::endl;
		//		return sendErrorMsg("501", "Not Implemented","Server doesn't implement this method");
		//	}
		//}

		//std::string content;
		//for (int i=0;i<nread;++i)
		//{
		//	content.push_back(extrabuf[i]);
		//}
		//msg+=content;

		//printf("\n result  nread:%d new  msg: \n\n %s \n",nread,msg.c_str());
		//strResult=msg;
		sleep(5);
		std::cout << "403 Forbidden: Server couldn't read this file  fileName: " << _fileName<<std::endl;
		return sendErrorMsg("501", "Not Implemented","Server doesn't implement this method");

		//ofstream fout("./home4.html");
		//fout <<strResult; // fout用法和cout一致, 不过是写到文件里面去
		//return strResult;

	}
	
	getFileType();
	std::string msg = "HTTP/1.1 200 OK\r\n";
	msg += "Server: Tiny Web Server\r\n";
	char tmp[32]={0};
	sprintf(tmp,"%d",fileInfo.st_size);
	msg += "Content-length: " + std::string(tmp) + "\r\n";
	msg += "Content_type: " + _fileType + "\r\n\r\n";
	int fd = open(_fileName.c_str(), O_RDONLY, 0);

	char extrabuf[65535];
	char *ptr = extrabuf;
	int nleft = 65535;
	int nread;
	while((nread = read(fd, ptr, nleft)) < 0)
	{
		if(errno == EINTR)
			nread = 0;
		else 
		{
			std::cout << "403 Forbidden: Server couldn't read this file." << std::endl;
			return sendErrorMsg("501", "Not Implemented","Server doesn't implement this method");
		}
	}

	std::string content;
	for (int i=0;i<nread;++i)
	{
		content.push_back(extrabuf[i]);
	}
	msg+=content;

	printf("\n result  msg: \n\n %s \n",msg.c_str());
	strResult=msg;
    return strResult;
}

void Parser::parseLine()
{
    std::string::size_type lineBegin = 0;   // 正在解析的行的行首索引
    std::string::size_type checkIndex = 0;  // 正在解析的字符索引

    while(checkIndex < _request.size())
    {
        // 如果当前字符是'\r'，则有可能读到一行
        if(_request[checkIndex] == '\r')
        {
            // 如果当前字符是最后一个字符则说明请求没有读取完整
            if((checkIndex + 1) == _request.size())
            {
                std::cout << "Request not to read the complete." << std::endl;
                return;
            }
            // 如果下一个字符是'\n'，则说明我们读取到了完整的一行
            else if(_request[checkIndex+1] == '\n')
            {
                _lines.push_back(std::string(_request, lineBegin,
                            checkIndex - lineBegin));
                checkIndex += 2;
                lineBegin = checkIndex;
            }
            else
            {
                std::cout << "Request error." << std::endl;
                return;
            }
        }
        else
            ++checkIndex;
    }
    return;
}

void Parser::parseRequestLine()
{
    assert(_lines.size() > 0);
    std::string requestLine = _lines[0];

    // first_ws指向请求行的第一个空白字符(' '或'\t')

	std::string::iterator first_ws=requestLine.begin();
	bool find=false;
	while(first_ws!=requestLine.end())
	{
		if (*first_ws == ' ' || *first_ws == '\t')
		{
			find=true;
			break;
		}
		++first_ws;
	}

	//// 如果请求行中没有出现空白则请求必定有错误
	if (!find)
	{
		std::cout << "Request error." << std::endl;
		return;
	}
	//// 截取请求方法
	_parseResult.method =std::string(requestLine.begin(), first_ws);

    // reverse_last_ws指向请求行中的最后一个空白字符(' '或'\t')
	std::string::reverse_iterator reverse_last_ws=requestLine.rbegin();
	find=false;
	while(reverse_last_ws!=requestLine.rend())
	{
		if (*reverse_last_ws == ' ' || *reverse_last_ws == '\t')
		{
			find=true;
			break;
		}
		++reverse_last_ws;
	}

	std::string::iterator last_ws=reverse_last_ws.base();
    _parseResult.version = std::string(last_ws, requestLine.end());

    while((*first_ws == ' ' || *first_ws == '\t') && first_ws != requestLine.end())
        ++first_ws;

    --last_ws;
    while((*last_ws == ' ' || *last_ws == '\t') && last_ws != requestLine.begin())
        --last_ws;

    _parseResult.uri = std::string(first_ws, last_ws + 1);
}

void Parser::parseHeaders()
{
	assert(_lines.size() > 0);
	for(int i = 1; i < _lines.size(); ++i)
	{
        if(_lines[i].empty()) // 如果遇到空行说明请求解析完毕
            return;
        else if(strncasecmp(_lines[i].c_str(), "Host:", 5) == 0) // 处理"Host"头部字段
        {
            std::string::iterator iter = _lines[i].begin() + 5;
            while(*iter == ' ' || *iter == '\t')
                ++iter;
            _parseResult.host = std::string(iter, _lines[i].end());
        }
        else if(strncasecmp(_lines[i].c_str(), "Connection:", 11) == 0) // 处理"Connection"头部字段
        {
            std::string::iterator iter = _lines[i].begin() + 11;
            while(*iter == ' ' || *iter == '\t')
                ++iter;
            _parseResult.connection = std::string(iter, _lines[i].end());
        }
        else
        {
            // 其他头部字段暂时忽略
        }
    }
}
