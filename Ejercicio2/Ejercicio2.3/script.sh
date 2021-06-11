%%bash

DIR=$(pwd)
dd if=/dev/zero of=/tmp/disk.img bs=1024 count=100k
sudo -S mkfs -t vfat -b 1024 /tmp/disk.img < $DIR/password

mkdir /tmp/disk
sudo -S mount -t vfat -o defaults,loop /tmp/disk.img /tmp/disk < $DIR/password
cd /tmp/disk

sudo -S dd if=/dev/urandom of=file.bin bs=1024 count=1 seek=0 < $DIR/password
ls -la file.bin
du -hs file.bin

sudo -S rm file.bin < $DIR/password
sudo -S dd if=/dev/urandom of=file.bin bs=1024 count=1 seek=11 < $DIR/password
echo "TERCERA"
ls -la file.bin
echo "TERCERA"
du -hs file.bin

sudo -S rm file.bin < $DIR/password
sudo -S dd if=/dev/urandom of=file.bin bs=1024 count=1 seek=12 < $DIR/password
ls -la file.bin
du -hs file.bin

sudo -S rm file.bin < $DIR/password
sudo -S dd if=/dev/urandom of=file.bin bs=1024 count=1 seek=268 < $DIR/password
ls -la file.bin
du -hs file.bin


cd $DIR
sudo -S umount /tmp/disk < password
sudo -S rm -rf /tmp/disk < password