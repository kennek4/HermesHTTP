import requests
import threading
import time
import argparse


def get_args() -> tuple:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "client_count",
        type=int,
        help="How many clients should simultaneously connect to the IP.",
    )

    parser.add_argument(
        "-i", "--ip", type=str, help="The IP that all clients should connect to."
    )

    parser.add_argument(
        "-p", "--port", type=str, help="The Port to connect to for the given IP."
    )

    args = parser.parse_args()

    # Set defaults
    client_count: int = args.client_count
    ip = "localhost"
    if args.ip is not None:
        ip = args.ip

    port = "8080"
    if args.port is not None:
        port = args.port

    return (client_count, ip, port)


def make_request(ip: str):
    requests.get(ip)


def main():
    (client_count, ip, port) = get_args()

    _THREAD_COUNT: int = client_count
    threads: list[threading.Thread] = list()

    _IP: str = f"http://{ip}:{port}"

    for num in range(_THREAD_COUNT):
        thread: threading.Thread = threading.Thread(target=make_request, args=(_IP,))
        threads.append(thread)

    _START_TIME = time.time()
    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()
    _END_TIME = time.time()

    print(f"Time to process {_THREAD_COUNT} client(s): {_END_TIME - _START_TIME:.5f}s")


if __name__ == "__main__":
    main()
