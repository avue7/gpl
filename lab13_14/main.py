#!/usr/bin/python3.5

import math
import sys
import ipaddress

response = input("\nPlease enter the number of the job you would like to perform:\n\n  1. For a maximum number of hosts on a subnet, determine the mask needed.\n  2. Given a host IP address and a mask, determine the subnet IP.\n  3. Given the subnet IP and mask, determine the broadcast IP.\n  4. Given the subnet IP and mask, determine the first valid host IP address.\n  5. Given a host IP and mask, determine the valid host IP address range.\n  6. Given a subnet IP and mask, determine if it is a valid subnet IP.\n  7. Exit.\n\nResponse: ")

# If user wants to determine mask needed
if response == "1":
   max_host_string = input("\nPlease enter the maximum number of hosts or quit(q): ")
   if max_host_string != "q":
      max_hosts = int(max_host_string)
      # 1. Take the max hosts and conver it to the nth power with base 2. 
      # Must account for network ip and broadcast ip so add 2 to max_hosts. 
      nth_power = math.log2(max_hosts+2)
      n = math.ceil(nth_power)
      # 2. Subtract that number from total CIDR (32..32-bits)
      CIDR = 32 - n
      # print(CIDR) **keep for debugging
      # 3. Need a way to store and calculate subnet mask...use 4-demension array
      subnet_mask = [0, 0, 0, 0]
      for i in range(CIDR):
          subnet_mask[int(i/8)] = subnet_mask[int(i/8)] + (1 << (7 - i % 8))
        # 4. Calculation is down print networ mask, need delimiter "." and join().
      print("Your network mask should be set to: ", ".".join(map(str, subnet_mask)), "\n")
   else:
      print("\nUser quit! Goodbye!\n")
      exit(0)
# If user wants subnet IP
elif response == "2":
     host_ip_string = input("\nPlease enter a host IP or quit(q): ")
     if host_ip_string == "q":
        print("User quit! Goodbye!\n")
        exit(0)
     subnet_mask_string = input("Please enter a subnet mask or quit(q): ")
     if subnet_mask_string != "q":
        host_ip = host_ip_string.split(".")
        subnet_mask = subnet_mask_string.split(".")
        subnet_ip = []
        for i in range(4):
            subnet_ip.append(int(host_ip[i]) & int(subnet_mask[i]))
        print("Your subnet IP should be: ", ".".join(map(str, subnet_ip)))
     else:
        print("User quit! Goodbye!\n")
        exit(0)
# If user wants the broadcast IP
elif response == "3":
     subnet_ip_string = input("\nPlease enter a subnet IP or quit(q): ")
     if subnet_ip_string == "q":
        print("User quit! Goodbye!\n")
        exit(0)
     subnet_mask_string = input("Please enter a subnet mask or quit(q): ")
     if subnet_mask_string != "q":
        ip = ipaddress.ip_network(subnet_ip_string+"/"+subnet_mask_string)
        print("Your broadcast ip should be: ", ip.broadcast_address)   
     else:
        print("User quit! Goodbye!\n")
        exit(0)
# If user wants do determine the first valid host ip address.
elif response == "4":
     subnet_ip_string = input("\nPlease enter a subnet IP or quit(q): ")
     if subnet_ip_string == "q":
        print("User quit! Goodbye!\n")
        exit(0)
     subnet_mask_string = input("Please enter a subnet mask or quit(q): ")
     if subnet_mask_string != "q":
        subnet_ip = subnet_ip_string.split(".")
        subnet_mask = subnet_mask_string.split(".")
        count=1
        host_first = []
        for i in range(4):
            if count != 4 or subnet_mask[i] == "255":
               count+=1
               host_first.append(subnet_ip[i])
            else:
               if count == 4:
                  host_first.append(int(subnet_ip[i])+ 1)
               count+=1
        print("First valid host ip is: ", ".".join(map(str, host_first)))
     else:
        print("User quit! Goodbye!\n")
        exit(0)
elif response == "5":
     host_ip_string = input("\nPlease enter a host IP or quit(q): ")
     if host_ip_string == "q":
        print("User quit! Goodbye!\n")
        exit(0)
     subnet_mask_string = input("Please enter a subnet mask or quit(q): ")
     if subnet_mask_string != "q":
        host_ip = host_ip_string.split(".")
        subnet_mask = subnet_mask_string.split(".")
        subnet_ip = []
        host_first = []
        host_last = []
        count=1
        for i in range(4):
            subnet_ip.append(int(host_ip[i]) & int(subnet_mask[i]))
        for i in range(4):
            if subnet_mask[i] == "255":
               count+=1
               host_first.append(subnet_ip[i])
               host_last.append(subnet_ip[i])
            else:
               if count == 4:
                  n = 256-int(subnet_mask[i])
                  host_first.append(int(subnet_ip[i])+1)
                  host_last.append(int(subnet_ip[i]+(n-2)))
                  count+=1
               else:
                  n = 256-int(subnet_mask[i])
                  host_first.append(subnet_ip[i])
                  host_last.append(int(subnet_ip[i]+(n)))
                  count+=1
        print("Range for valid host IP should be: ", ".".join(map(str, host_first)),"-",".".join(map(str, host_last)), "\n")
     else:
        print("User quit! Goodbye!\n")
        exit(0)
elif response == "6":
     subnet_ip_string = input("\nPlease enter a subnet IP or quit(q): ")
     if subnet_ip_string == "q":
        print("User quit! Goodbye!\n")
        exit(0)
     subnet_mask_string = input("Please enter a subnet mask or quit(q): ")
     if subnet_mask_string != "q":
        status=ipaddress.ip_address(subnet_ip_string+"/"+subnet_mask_string) 
        print (status)
     else:
        print("\nUser exit! Goodbye!\n")
        exit(0)
                  
elif response == "7":
     print("\nUser exit! Goodbye!\n")
     exit(0)
