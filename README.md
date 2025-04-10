**Build Bootloader**

**0\. Configure Build Server**  
**전체적인 내용은 240.04.2에서 확인 됨**  
Ubuntu-24.04.2 설치 (Ubuntu-20.04 이상 가능 \- 패키지 미세 조정 필요)

아래 패키지 설치(24.04)  
apt install build-essential gcc-aarch64-linux-gnu bison flex libssl-dev libncurses-dev unzip uuid uuid-dev device-tree-compiler gettext pkgconf swig libyaml-dev

아래 패키지 설치(20.04)  
apt install build-essential gcc-aarch64-linux-gnu bison flex libssl-dev libncurses5 libncurses5-dev unzip uuid uuid-dev device-tree-compiler gettext pkgconf swig libyaml-dev

**1\. Create Directory**  
lssnow@lss:\~$ mkdir bootloader  
lssnow@lss:\~$ cd bootloader

아래 위치 참고  
[https://github.com/mtk-openwrt/u-boot](https://github.com/mtk-openwrt/u-boot)

lssnow@lss:\~/bootloader$ git clone https://github.com/mtk-openwrt/u-boot.git  
Cloning into 'u-boot'...  
remote: Enumerating objects: 1047707, done.  
remote: Counting objects: 100% (4/4), done.  
remote: Compressing objects: 100% (3/3), done.  
remote: Total 1047707 (delta 1), reused 1 (delta 1), pack-reused 1047703 (from 1\)  
Receiving objects: 100% (1047707/1047707), 286.48 MiB | 20.46 MiB/s, done.  
Resolving deltas: 100% (832463/832463), done.  
Updating files: 100% (35984/35984), done.

하지만, **이건 RTL8370MB Switch 드라이버가 포팅되지 않아 사용하지 않음**

**2\. Download ATF**  
아래 위치 참고  
[https://github.com/mtk-openwrt/arm-trusted-firmware-mtk](https://github.com/mtk-openwrt/arm-trusted-firmware-mtk)

lssnow@lss:\~/bootloader$ git clone https://github.com/mtk-openwrt/arm-trusted-firmware-mtk.git  
Cloning into 'arm-trusted-firmware-mtk'...  
remote: Enumerating objects: 147292, done.  
remote: Counting objects: 100% (23774/23774), done.  
remote: Compressing objects: 100% (2093/2093), done.  
remote: Total 147292 (delta 22144), reused 21681 (delta 21681), pack-reused 123518 (from 1\)  
Receiving objects: 100% (147292/147292), 44.42 MiB | 20.22 MiB/s, done.  
Resolving deltas: 100% (98340/98340), done.

**3\. Build U-boot**  
lssnow@lss:\~/bootloader$ cp \~/images/uboot-mtk-20220606.rtl8370mb.tar.gz .  
lssnow@lss:\~/bootloader$ tar zxvf uboot-mtk-20220606.rtl8370mb.tar.gz  
lssnow@lss:\~/bootloader$ cd uboot-mtk-20220606  
**make V=1 CROSS\_COMPILE=/usr/bin/aarch64-linux-gnu- mt7981\_spim\_nand\_rfb\_with\_rtl8370mb\_defconfig**  
**make V=1 CROSS\_COMPILE=/usr/bin/aarch64-linux-gnu-**  
….  
 /usr/bin/aarch64-linux-gnu-objdump \-t u-boot \> u-boot.sym  
  ./tools/mkimage \-T mtk\_image \-a 0x41e00000 \-e 0x41e00000 \-n "media=snand;nandinfo=2k+64" \-d u-boot.bin u-boot-mtk.bin \>/dev/null  && cat /dev/null

**4\. Build ATF**  
lssnow@lss:\~/bootloader$ cd arm-trusted-firmware-mtk/

한줄로 모두 입력  
**BL33 option 위치 명확하게 설정**

**make \-f ./Makefile PLAT="mt7981" CROSS\_COMPILE="/usr/bin/aarch64-linux-gnu-" BOOT\_DEVICE="spim-nand" NMBM=1 NAND\_TYPE="spim:2k+64" DRAM\_USE\_DDR4=0 DDR3\_FREQ\_2133=1 BOARD\_BGA=1 LOG\_LEVEL=20 BL33="../uboot-mtk-20220606/u-boot.bin"  all fip**  
….  
….  
Built /home/lssnow/bootloader/arm-trusted-firmware-mtk/build/mt7981/release/fip.bin successfully

lssnow@lss:\~/bootloader/arm-trusted-firmware-mtk/build/mt7981/release$ la  
total 1696  
drwxrwxr-x 8 lssnow lssnow    4096 Apr 10 12:31 .  
drwxrwxr-x 3 lssnow lssnow    4096 Apr 10 12:31 ..  
drwxrwxr-x 3 lssnow lssnow    4096 Apr 10 12:31 bl2  
drwxrwxr-x 3 lssnow lssnow   12288 Apr 10 12:31 bl31  
drwxrwxr-x 2 lssnow lssnow    4096 Apr 10 12:31 fdts  
drwxrwxr-x 2 lssnow lssnow    4096 Apr 10 12:31 lib  
drwxrwxr-x 2 lssnow lssnow    4096 Apr 10 12:31 libc  
drwxrwxr-x 2 lssnow lssnow    4096 Apr 10 12:31 libfdt  
\-rwxrwxr-x 1 lssnow lssnow  239677 Apr 10 12:31 bl2.bin  
\-rw-rw-r-- 1 lssnow lssnow  242528 Apr 10 12:31 **bl2.img**  
\-rwxrwxr-x 1 lssnow lssnow   37529 Apr 10 12:31 bl31.bin  
\-rw-rw-r-- 1 lssnow lssnow 1163641 Apr 10 12:31 **fip.bin**

**5\. Upgrade BL2 & FIP**  
 ![스크린샷 2025-04-10 오후 9 34 50](https://github.com/user-attachments/assets/6afdc4c9-e415-4feb-84cc-644c5370ef7f)
**bl2.img 사용**

![스크린샷 2025-04-10 오후 9 35 13](https://github.com/user-attachments/assets/8304825a-a58a-4b3d-ace5-1f8a9b5bd5f6)
**fip.bin 사용**

**6\. Example Test**  
   
![스크린샷 2025-04-10 오후 9 43 26](https://github.com/user-attachments/assets/a8516923-90ee-4484-9646-c9aa7bfb02fe)

**bootmenu**

![스크린샷 2025-04-10 오후 9 43 04](https://github.com/user-attachments/assets/2489f93f-1636-42e5-b709-011d8c8f5ab9)

**reset**
