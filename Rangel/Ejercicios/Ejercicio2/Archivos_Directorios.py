#!/usr/bin/python

from os import listdir
import os, sys

archivos = 0
carpetas = 0
total = 0
#ruta = "/usr/bin"
if len(sys.argv) < 2:
	print "Falta ruta. Ejemplo: /usr/bin"
else:
	ruta = sys.argv[1]

	for h in listdir(ruta):
		print h

	num_arch = [f for f in os.listdir(ruta)
		if os.path.isfile(os.path.join(ruta, f))]
	for arch in num_arch:
		archivos = archivos+1


	num_car = [i for i in os.listdir(ruta)
		if os.path.isdir(os.path.join(ruta, i))]
	for car in num_car:
		carpetas = carpetas+1

	total = carpetas + archivos

	print
	print "Archivos: ",archivos
	print "Carpetas: ",carpetas
	print "Total: ", total
	print 
