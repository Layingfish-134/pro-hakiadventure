#include"../thirdparty/httplib.h"
int main()
{
	httplib::Client client("localhost:25565");

	httplib::Result result = client.Post("/hello");

	if (!result || result->status != 200)
	{
		std::cout << "hello failed" << std::endl;

		return -1;
	}

	std::cout << result->body << std::endl;

	system("pause");

	return 0;
}