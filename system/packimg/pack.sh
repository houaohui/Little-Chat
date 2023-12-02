#!/bin/bash

_UBOOT_SIZE=1

###第一个分区(FAT)大小,单位MiB##
_P1_SIZE=32

###TF卡镜像文件名称###
_IMG_FILE='Mwatch-f1c200s.img'

###TF卡镜像文件大小, 单位MiB###
_IMG_SIZE=1300

temp_root_dir=$PWD

_UBOOT_FILE="${temp_root_dir}/data/u-boot-sunxi-with-spl.bin"
#_SPLASH_BMP_FILE="${temp_root_dir}/data/splash.bmp"
#_BOOT_SCR_FILE="${temp_root_dir}/data/boot.scr"
_KERNEL_IMAGE_FILE="${temp_root_dir}/data/zImage"
_DTB_FILE="${temp_root_dir}/data/mwatch.dtb"
_ROOTFS_TGZ_FILE="${temp_root_dir}/data/rootfs.tar"

        ###初始化镜像文件###
        dd if=/dev/zero of=$_IMG_FILE bs=1M count=$_IMG_SIZE

        ###判断镜像文件是否初始化成功###
        if [ $? -ne 0 ]
        then
                echo  "getting error in creating dd img!"
                exit
        fi


        ###获取一个循环设备###
        _LOOP_DEV=$(sudo losetup -f)
        #echo ${_LOOP_DEV}



        ##再次判断此设备是否存在###
        if [ -z $_LOOP_DEV ]
        then
                echo  "can not find a loop device!"
                exit
        fi

        ###把镜像文件和循环设备关联###
        sudo losetup $_LOOP_DEV $_IMG_FILE
        if [ $? -ne 0 ]
        then
                echo  "dd img --> $_LOOP_DEV error!"
                sudo losetup -d $_LOOP_DEV >/dev/null 2>&1 && exit
        fi
        echo  "--->creating partitions for tf image ..."
        #blockdev --rereadpt $_LOOP_DEV >/dev/null 2>&1
        # size only can be integer



###分区###
cat <<EOT |sudo  sfdisk ${_IMG_FILE}
${_UBOOT_SIZE}M,${_P1_SIZE}M,c
,,L
EOT


###格式化###
        sleep 2
        sudo partx -u $_LOOP_DEV
        sudo mkfs.vfat -n boot ${_LOOP_DEV}p1 ||exit
        sudo mkfs.ext4 -L rootfs ${_LOOP_DEV}p2 ||exit
        if [ $? -ne 0 ]
        then
                echo  "error in creating partitions"
                sudo losetup -d $_LOOP_DEV >/dev/null 2>&1 && exit
                #sudo partprobe $_LOOP_DEV >/dev/null 2>&1 && exit
        fi

        ###u-boot写到TF卡8K偏移处###
        #pack uboot
        echo  "--->writing u-boot-sunxi-with-spl to $_LOOP_DEV"
        # sudo dd if=/dev/zero of=$_LOOP_DEV bs=1K seek=1 count=1023  # clear except mbr
        sudo dd if=$_UBOOT_FILE of=$_LOOP_DEV bs=1024 seek=8
        if [ $? -ne 0 ]
        then
                echo  "writing u-boot error!"
                sudo losetup -d $_LOOP_DEV >/dev/null 2>&1 && exit
                #sudo partprobe $_LOOP_DEV >/dev/null 2>&1 && exit
        fi



        ###新建 p1,p2 目录，并挂载TF卡两个分区###
        sudo sync
        mkdir -p ${temp_root_dir}/output/p1 >/dev/null 2>&1
        mkdir -p ${temp_root_dir}/output/p2 > /dev/null 2>&1
        sudo mount ${_LOOP_DEV}p1 ${temp_root_dir}/output/p1
        sudo mount ${_LOOP_DEV}p2 ${temp_root_dir}/output/p2
        echo  "--->copy boot and rootfs files..."
        sudo rm -rf  ${temp_root_dir}/output/p1/* && sudo rm -rf ${temp_root_dir}/output/p2/*


        ###复制zImage, dtb, boot.scr, splash.bmp 等文件到第一分区 ###
        sudo cp ${_KERNEL_IMAGE_FILE} ${temp_root_dir}/output/p1/ &&\
        sudo cp ${_DTB_FILE} ${temp_root_dir}/output/p1/ &&\
        #sudo cp ${_BOOT_SCR_FILE} ${temp_root_dir}/output/p1/ &&\
        #sudo cp ${_SPLASH_BMP_FILE} ${temp_root_dir}/output/p1/ &&\
        echo "--->p1 done~"

        ###解压 rootfs.tgz 到第二分区###
        sudo tar xvf ${_ROOTFS_TGZ_FILE} -C ${temp_root_dir}/output/p2/ &&\
        echo "--->p2 done~"



        ###同步, 等待, 卸载, 退出###
        sudo sync
        sleep 2
        sudo umount ${temp_root_dir}/output/p1 ${temp_root_dir}/output/p2  && sudo losetup -d $_LOOP_DEV
        if [ $? -ne 0 ]
        then
                echo  "umount or losetup -d error!!"
                exit
        fi
	sudo rm ${temp_root_dir}/output/ -r

