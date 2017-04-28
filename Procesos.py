#!/usr/bin/python

import sys, os, subprocess

menu = 0

def procesos_activos():
	farchivo = open ('/proc/stat', 'r')
	for line in farchivo:
		if ('cpu') in line:
			print line
		elif ('procs_running') in line:
			print line
	farchivo.close()

def procesador():
	farchivo = open ('/proc/cpuinfo', 'r')
	for line in farchivo:
		if ('processor') in line:
			print line
		elif ('vendor_id') in line:
			print line
		elif ('model name') in line:
			print line
		elif ('cache size') in line:
			print line
		elif ('cpu MHZ') in line:
			print line
	farchivo.close()

def memoria():
	farchivo = open ('/proc/meminfo', 'r')
	for line in farchivo:
		if ('MemTotal') in line:
			print line
		elif ('MemFree') in line:
			print line
		elif ('Buffers') in line:
			print line
	farchivo.close()

def disco_duro():
	subprocess.call(['df', '-h'])

def dispositivos():
	farchivo = open ('/proc/ioports', 'r')
	farchivo.close()

opcion = 1
while opcion == 1:
	os.system('clear')
	print "Practica 1"
	print "Caracteristicas del CPU"
	print "1. Procesos Activos"
	print "2. Memoria RAM usada"
	print "3. Porcentaje de disco duro usado"
	print "4. Caracteristicas del procesador"
	print "5. Dispositivos conectados"
	print "Elige una opcion: "

	menu = input()
	while (menu <= 0 or menu > 5):
		print "Selecciona otra opcion"
		menu = input()
	else:
		if menu == 1:
			procesos_activos()
		elif menu == 2:
			memoria()
		elif menu == 3:
			disco_duro()
		elif menu == 4:
			procesador()
		else:
			dispositivos()
	print "Desea buscar otra caracteristica de la computadora?"
	print "1. SI 		2.NO"
	opcion = input()
	if opcion == 1:
		continue
	else:
		os.system('clear')
		sys.exit(1)