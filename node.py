import socket
import threading
import os
import time
import datetime

def handle_incoming_messages(sock):
    while True:
        message, addr = sock.recvfrom(1024)
        print(f"Received message from {addr}: {message.decode('utf-8')}")

def send_messages(sock, peers):
    while True:
        for peer in peers:
            message = f"hi at time {datetime.datetime.now()}"
            sock.sendto(message.encode('utf-8'), peer)
            print(f"Sent 'hi' to {peer}")
        time.sleep(5)

def main():
    hostname = socket.gethostname()
    my_ip = socket.gethostbyname(hostname)
    print(my_ip)
    my_port = 8000

    peers = [
        ("172.18.0.2", 8000),
        ("172.18.0.3", 8000),
        ("172.18.0.4", 8000),
        ("172.18.0.5", 8000),
        ("172.18.0.6", 8000),
    ]
    peers = [peer for peer in peers if peer != (my_ip, my_port)]

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((my_ip, my_port))

    threading.Thread(target=handle_incoming_messages, args=(sock,), daemon=True).start()
    send_messages(sock, peers)

if __name__ == "__main__":
    main()
