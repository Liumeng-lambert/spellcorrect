 ///
 /// @file    tcp.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-03 16:15:36
 ///

#ifndef _TCP_H_
#define _TCP_H_
#include <iostream>
#include <memory>
#include <functional>
#include "socket.hpp"

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection: public std::enable_shared_from_this<TcpConnection>{
public:
	TcpConnection();
	TcpConnection(int sockfd);
	~TcpConnection();
	typedef std::function<void (const TcpConnectionPtr &)> TcpConnectionCallback;
	std::string receive();
	void send(const std::string & msg);
	void shutdown();
	void set_connection_callback(TcpConnectionCallback cb);
	void set_message_callback(TcpConnectionCallback cb);
	void set_close_callback(TcpConnectionCallback cb);
	void handle_connection_callback();
	void handle_message_callback();
	void handle_close_callback();
	std::string to_string();
private:
	Socket _socket;
	SocketIO _sockIO;
	const InetAddress _local_addr;
	const InetAddress _peer_addr;
	bool _is_shutdown_write;
	TcpConnectionCallback _on_connection_cb;
	TcpConnectionCallback _on_message_cb;
	TcpConnectionCallback _on_close_cb;

};
#endif
