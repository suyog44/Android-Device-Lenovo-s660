How to Build

kernel
======
1. Get the prebuilt cross compiler from AOSP website
   $ git clone https://android.googlesource.com/platform/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.7

2. Copy required cross compiler to your alps folder:
    ex. ~/alps/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.7

3. Run the build command under your alps folder
   $ ./mk vv38 n k

output Binary Files:
======
1. When the build process is completed, the generated kernel can be found in the following path:
   alps/out/target/product/vv38/kernel_vv38.bin
2. If you are building a rom with this bin file, copy it into your build's output folder and rename it to "kernel".
   then, you can do following command to generate the file of boot.img. 
   $ ./mk vv38 bootimage
3. you can flash this boot.img to your phone device, the phone can power on normally.

For get open source code or additional information:
=========================== 
You can Contact Lenovo support for information on obtaining Open Source code.
