#include"../thirdparty/httplib.h"

#include<mutex>
#include<fstream>
#include<string>

std::mutex g_mutex;
//全局互斥锁
std::string str_text;
//需要的文本

int progress_1 = -1;
int progress_2 = -1;


void on_hello(const httplib::Request& req, httplib::Response& res)
{
	std::lock_guard<std::mutex> lock(g_mutex);

	std::cout << "hello from client" << std::endl;

	res.set_content("Hello from server", "text/plain");

	
}

int main()
{
	std::ifstream file("text.txt");
	if (!file.good())
	{
		MessageBox(nullptr, L"无法打开文本文件", L"启动失败", MB_OK | MB_ICONERROR);
		return -1;
	}
	std::stringstream str_stream;
	str_stream << file.rdbuf();
	str_text = str_stream.str();

	file.close();

	httplib::Server server;

	server.Post("/login", [&](const httplib::Request& req,  httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(g_mutex);

			if (progress_1 >= 0 && progress_2 >= 0)
			{
				res.set_content("-1","text/plain");
				return;
			}

			res.set_content((progress_1 >= 0) ? "2" : "1", "text/plain");
			(progress_1 >= 0) ? (progress_2 = 0) : (progress_1 = 0);
			return;
		});

	server.Post("/query_text", [&](const httplib::Request& req, httplib::Response& res)
		{
			res.set_content(str_text, "text/plain");
		}
	);

	server.Post("/update_1", [&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(g_mutex);

			progress_1 = std::stoi(req.body);
			//存储玩家1的进度

			res.set_content(std::to_string(progress_1), "text/plain");
			//给玩家1玩家2的进度以绘图
		}
	);

	server.Post("/update_2", [&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(g_mutex);

			progress_2 = std::stoi(req.body);
			//存储玩家1的进度

			res.set_content(std::to_string(progress_2), "text/plain");
			//给玩家1玩家2的进度以绘图
		}
	);

	server.listen("0.0.0.0", 25565);

	return 0;
}