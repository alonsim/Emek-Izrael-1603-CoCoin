import os

def create_p2p_node(name, ip):
    os.system(f'docker run -d --net p2p-network --ip {ip} -e MY_IP={ip} --name {name} node ')


def main():
    nodes = [
        {"name": "p2p-node2", "ip": "172.18.0.3"},
        {"name": "p2p-node3", "ip": "172.18.0.4"},
        {"name": "p2p-node4", "ip": "172.18.0.5"},
        {"name": "p2p-node5", "ip": "172.18.0.6"},
    ]

    for node in nodes:
        create_p2p_node(node["name"], node["ip"])

if __name__ == "__main__":
    main()

#docker network create --subnet=172.18.0.0/16 p2p-network
#docker rm -v -f $(docker ps -aq)