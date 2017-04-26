#!/usr/bin/python

import subprocess, time

hosts = ('8.8.8.8', 'kernel.org', 'yahoo.com')
def ping(hosts):
	ret = subprocess.call(['ping', '-c', '3', '-W', '5', hosts],
		stdout=open('/dev/null', 'w'),
		stderr=open('/dev/null', 'w'))
	return ret==0
def net_is_up():
	print "[%s] Checking if network is up..." %time.strftime("%Y-%m-%d %H:%M:%S")

	xstatus = 1

	for h in hosts:			#HACE PING EN LAS 3 DIRECCIONES DE HOSTS
		if ping(h):
			print "[%s] Hay conexion!" %time.strftime("%Y-%m-%d %H:%M:%S")
			xstatus = 0
			break

		if xstatus:
			print "[%s] No hay conexion!" %time.strftime("%Y-%m-%d %H:%M:%S")

		return xstatus

quit(net_is_up())
