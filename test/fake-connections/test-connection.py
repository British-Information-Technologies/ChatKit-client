# Credit: https://www.geeksforgeeks.org/python-binding-and-listening-with-sockets/

import socket
import sys
  
# specify Host and Port
HOST = 'localhost'
PORT = 5789
   
soc = socket.socket(
    socket.AF_INET6,         # append 6 for ipv6 or remove for ipv4
    socket.SOCK_STREAM
)
  
try:
    # With the help of bind() function
    # binding host and port
    soc.bind((HOST, PORT))
      
except socket.error as message: 
    # if any error occurs then with the
    # help of sys.exit() exit from the program
    print(
        'Bind failed. Error Code : ' +
        str(message[0]) +
        ' Message ' + 
        message[1]
    )
    
    sys.exit()
     
# print if Socket binding operation completed   
print('Socket binding operation completed')
  
# With the help of listening () function
# starts listening
soc.listen(9)
  
conn, address = soc.accept()
# print the address of connection
print('Connected with ' + address[0] + ':' + str(address[1]))

stop = False
while(not stop):
    response = conn.recv(1024)
    
    print('recv: ' + response.decode())

    if input("Stop?[y/N]") == 'y':
        stop = True

conn.close()
soc.close()
print('Shutting down')