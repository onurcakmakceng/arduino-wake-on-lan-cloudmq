import socket
import sys

if len(sys.argv) < 3:
    print("Usage: send_magic_packet.py <ADR> <MAC>     (example: 192.168.1.255 00:11:22:33:44:55)")
    sys.exit(1)
port=4343
mac = sys.argv[2]
data = ''.join(['FF' * 6, mac.replace(':', '') * 16])
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

if sys.version_info[0] < 2.7:
    # hexadecimal string to byte array in Python ≤ 2.7
    sock.sendto(data.decode("hex"), (sys.argv[1], port))
else:
    # hexadecimal string to byte array in Python ≥ 3
    sock.sendto(bytes.fromhex(data), (sys.argv[1], port))
