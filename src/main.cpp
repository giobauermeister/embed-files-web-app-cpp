#include <iostream>
#include <fstream>
#include <httpserver.hpp>
#include "../build/_cmrc/include/cmrc/cmrc.hpp"  // Include CMakeRC header

CMRC_DECLARE(res);

using namespace httpserver;

class web_page_resource : public http_resource
{
private:
    std::string path;
    std::map<std::string, std::string> content_types{
        {".html", "text/html"},
        {".js", "text/javascript"},
        {".css", "text/css"},
        {".png", "image/png"},
        {".ico", "image/vnd.microsoft.icon"}
    };

    std::string get_content_type(const std::string &path)
    {
        // Find the file extension and return the content type
        size_t dot_position = path.rfind('.');
        if(dot_position != std::string::npos)
        {
            std::string extension = path.substr(dot_position);
            if(content_types.find(extension) != content_types.end())
            {
                return content_types[extension];
            }
        }
        return "application/octet-stream";
    }

public:
    std::shared_ptr<http_response> render(const http_request& req)
    {
        std::cout << std::string(req.get_method()) << ": " << std::string(req.get_path()) << std::endl;
        std::string path = std::string(req.get_path());
        auto fs = cmrc::res::get_filesystem();

        if(path == "/") path = "/index.html";

        // Remove leading "/" for cmrc paths
        if (!path.empty() && path[0] == '/') {
            path = path.substr(1);
        }

        // Check if the file exists in the embedded filesystem
        if (fs.exists(path)) {
            auto file = fs.open(path);
            std::string content(file.begin(), file.end());
            std::string content_type = get_content_type(path);
            return std::make_shared<string_response>(content, 200, content_type);
        } else {
            return std::make_shared<string_response>("Not found", 404);
        }
    }
};

int main() {
    std::cout << "Starting webserver..." << std::endl;    

    webserver ws = create_webserver(8081);

    web_page_resource wpr;
    ws.register_resource("/", &wpr, true);

    ws.start(true);

    return 0;
}