#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

struct Node 
{
    std::string name;
    std::string ip;
};

void create_p2p_node(const std::string& name, const std::string& ip) 
{
    std::string command = "docker run -d --net p2p-network --ip " + ip + " -e MY_IP=" + ip + " --name " + name + " node";
    system(command.c_str());
}

int main() 
{
    std::vector<Node> nodes = 
    {
        {"p2p-node2", "172.18.0.3"},
        {"p2p-node3", "172.18.0.4"},
        {"p2p-node4", "172.18.0.5"},
        {"p2p-node5", "172.18.0.6"},
    };

    for (const auto& node : nodes) 
    {
        create_p2p_node(node.name, node.ip);
    }

    return 0;
}
