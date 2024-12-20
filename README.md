# Example for configuring external RAM on Nuvoton's Mbed CE enabled boards

This is an example to demo configuring external RAM on Nuvoton's Mbed CE enabled boards.
It can be disable or enable external RAM, depending on target board.

Check out [Mbed CE](https://github.com/mbed-ce)
for details on Mbed OS community edition.

## Support development tools

Use cmake-based build system.
Check out [hello world example](https://github.com/mbed-ce/mbed-ce-hello-world) for getting started.

> **⚠️ Warning**
>
> Legacy development tools below are not supported anymore.
> - [Arm's Mbed Studio](https://os.mbed.com/docs/mbed-os/v6.15/build-tools/mbed-studio.html)
> - [Arm's Mbed CLI 2](https://os.mbed.com/docs/mbed-os/v6.15/build-tools/mbed-cli-2.html)
> - [Arm's Mbed CLI 1](https://os.mbed.com/docs/mbed-os/v6.15/tools/developing-mbed-cli.html)

For [VS Code development](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-VS-Code)
or [OpenOCD as upload method](https://github.com/mbed-ce/mbed-os/wiki/Upload-Methods#openocd),
install below additionally:

-   [NuEclipse](https://github.com/OpenNuvoton/Nuvoton_Tools#numicro-software-development-tools): Nuvoton's fork of Eclipse
-   Nuvoton forked OpenOCD: Shipped with NuEclipse installation package above.
    Checking openocd version `openocd --version`, it should fix to `0.10.022`.

## Configure External RAM for target board

### Example: disable EBI RAM for NUMAKER_PFM_NUC472 target

This target has on-board EBI RAM and it defaults to enabled.
To disable it, configure as below:

```json5
{
    "target_overrides": {
        "NUMAKER_PFM_NUC472": {
            "target.ebi-enable": false
        }
    }
}
```

### Example: Enable HyperRAM for NUMAKER_IOT_M467 target

This target doesn't have on-board HyperRAM.
If it is added and then to enable it, configure as below:

```json5
{
    "target_overrides": {
        "NUMAKER_IOT_M467": {
            "target.hbi-enable": true,
            "target.hbi-mfp-reg-list": "0x40000534, 0x4000057C, 0x40000590, 0x40000594",
            "target.hbi-mfp-reg-msk-list": "0xFFFFFF00, 0xFFFFFFFF, 0xFFFF0000, 0xFFFFFFFF",
            "target.hbi-mfp-reg-val-list": "0x10101000, 0x10101010, 0x10100000, 0x10101010"
        }
    }
}
```

> **ℹ️ Information**
>
> See [Enable HyperRAM on M460 series](https://github.com/mbed-ce/mbed-os/tree/master/targets/TARGET_NUVOTON/TARGET_M460#hyperram).

## Developer guide

In the following, we take **NuMaker-PFM-NUC472** board as an example for Mbed CE support.

### Build the example

1.  Clone the example and navigate into it
    ```
    $ git clone https://github.com/mbed-nuvoton/NuMaker-mbed-ce-XRAM-example
    $ cd NuMaker-mbed-ce-XRAM-example
    $ git checkout -f master
    ```

1.  Deploy necessary libraries
    ```
    $ git submodule update --init
    ```
    Or for fast install:
    ```
    $ git submodule update --init --filter=blob:none
    ```

1.  Compile with cmake/ninja
    ```
    $ mkdir build; cd build
    $ cmake .. -GNinja -DCMAKE_BUILD_TYPE=Develop -DMBED_TARGET=NUMAKER_PFM_NUC472
    $ ninja
    $ cd ..
    ```

### Flash the image

Flash by drag-n-drop built image `NuMaker-mbed-ce-XRAM-example.bin` or `NuMaker-mbed-ce-XRAM-example.hex` onto **NuMaker-PFM-NUC472** board

### Verify the result

On host terminal (115200/8-N-1), we should see heap memory is located at
`0x20000000` (IRAM) instead of `0x60000000` (EBI RAM).
