#!/bin/bash

# Monter le système de fichier
# temp_dir="$(mktemp -d)"
# TODO
# 

# Configuration du gadget
cd /sys/kernel/config/usb_gadget/
mkdir -p rit_attack
cd rit_attack
echo 0x1d6b > idVendor   # Linux Foundation
echo 0x0104 > idProduct  # Multifunction Composite Gadget
echo 0x0100 > bcdDevice # v1.0.0
echo 0x0200 > bcdUSB # USB2
mkdir -p strings/0x409
echo "badc0dedcafebabe" > strings/0x409/serialnumber
echo "Adjeba & Wuszko & Petit" > strings/0x409/manufacturer
echo "RIT gadget" > strings/0x409/product
mkdir -p configs/c.1/strings/0x409
echo "Config 1: USB Mass Storage" > configs/c.1/strings/0x409/configuration

# Configuration du module de stockage
mkdir -p functions/mass_storage.usb0/
echo "$mntpoint" > functions/mass_storage.0/lun.0/file

# Fin de la config
ln -s functions/mass_storage.usb0 configs/c.1/

# Démarrer le gadget en y associant un controlleur USB.
#TODO