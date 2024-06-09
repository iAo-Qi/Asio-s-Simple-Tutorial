#include <iostream>
#include <asio.hpp>

void ASIObase()
{
	//构造函数address(ip v4 || v6转换为地址) 
	//asio::ip::address::from_string(v4 || v6转换为地址); 
	//它俩功能一样! 缺点也都不能直接使用网址 
	// 如: asio::ip::address::from_string("www.baidu.com");

	asio::ip::address add = asio::ip::address::from_string("192.168.1.95");//将字符串ip转换为 地址

	//  asio::ip::address add2 = asio::ip::address::from_string("www.baidu.com");//抛出异常 Aborted

	std::cout << add.to_string() << std::endl; //打印出192.168.1.95;

	//添加端口
	asio::ip::tcp::endpoint endpoint(add, 2221);

	//打印完整的地址与端口号
	std::cout << endpoint.address() << ":" << endpoint.port() << std::endl;

	asio::ip::tcp::endpoint endpoint2(asio::ip::tcp::v4(), 8886);

	//打印 0.0.0.0:8886
	std::cout << endpoint2.address() <<":" << endpoint2.port() << std::endl;

	return;
}

void ASiOHostResolver() 
{
	//在过去较老的版本里可能会使用 io_service 当然现在也兼容asio::io_service
	//在io_service.hpp里 typedef io_context io_service; 所以 io_context与io_service同价值不同名
	//复制于chatgpt👉 boost::asio::io_service（或 io_context）是 Boost.Asio 中处理异步操作的核心组件。它管理异步操作的调度和执行，提供事件循环，并支持多线程处理。这使得它成为构建高性能、异步网络应用程序的基础。通过上述示例，您可以看到如何使用 io_service 进行定时器操作和简单的 TCP 异步操作。
	//说白了几乎任何事情都需要io_context
	asio::io_context io_context;

	//创建解析器对象
	asio::ip::tcp::resolver resolver(io_context);

	//asio::ip::tcp::resolver::query 可以用于解析 主机名称
	//第一个参数是指 主机名域名 第二个参数 可以填写端口或协议 如"80" "https" "ftp" .....

	asio::ip::tcp::resolver::query query("www.baidu.com","https");
	
	//迭代器 可以迭代 主机所有绑定的ip
	asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

	//迭代到最后 可能会返回未初始化 或 空的 asio::ip::tcp::resolver::iterator() 所以让它来当作结束条件
	//迭代包括ipv4 和ipv6! 可以使用 it->endpoint().address().is_v4() 来筛选ipv4 或ipv6
	for (asio::ip::tcp::resolver::iterator it= iterator; it!=asio::ip::tcp::resolver::iterator(); it++)
	{
		//我只想要ipv6
		if (it->endpoint().address().is_v6())
		{
			std::cout << "ipv6 -"<< it->endpoint() << std::endl;
		}
	}
	// ipv6 -[2408:871a : 2100 : 3 : 0 : ff : b025 : 348d] :443
	//	ipv6 -[2408:871a : 2100 : 2 : 0 : ff : b09f : 237] : 443

	return;
}

void ASIOsocket() 
{

}
int main()
{
	//ASIObase();
	ASiOHostResolver();
	return 0;
}