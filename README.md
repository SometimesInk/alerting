# Alerting

This program changes the color of your Hyprland windows' borders depending on your battery level.

To do so, the program is either called periodically at definite time intervals (systemd), or is called when your battery level decreases (using udev). As a note, I've had some problems with udev rules.

## Requirements

To use this program, you must have the following *things* installed:
 1. Hyprland (*obviously*)
 2. [GCC](https://archlinux.org/packages/core/x86_64/gcc/)
If the program cannot find a specific command, you can install it (`bc` for example).

## Configuring Hyprland

For this program to work, you have to source the `alerting.conf` file in your Hyprland config.

```conf
# ~/.config/hypr/hyprland.conf

source=~/.config/hypr/alerting.conf # Source the alerting file
...
```

This file entirely modified by the `script.sh` script.

> [!WARNING]
>
> For this to work, you have to remove or comment out the `col.active_border` property in the `general` section. I'm not sure how Hyprland handles duplicate properties, but I'm sure that'll lead to unnecessary problems.

## Configuring this Program

First of all, you should run the `./alerting.sh --compile` command in this directory to compile the *precompiler*. Whats the precompiler? you'll see later. Now you should take a look at the `alerting.ini` configuration file, it contains information about every single property.

> [!NOTE]
>
> If you're wondering why the final category in the configuration file is ambiguous, it is because it should not be touched if you don't have a good understanding of how the program works. The way this program functions will be described in a later section.

If you want to test what the color of your border will be at a certain percentage, you can use the `alerting.sh` script located in the same directory as this markdown file. You can call the command `./alerting.sh --run=...` to run the border changing script at a battery value of your choice. Read `./alerting.sh --help` and the *Main Script* section for more information.

### Modifying Paths

This programs contains a few paths that you have to change for the program to function. Here is the list of paths in the list and what you should change it to:

> [!NOTE]
>
> Name of the files are relative to the `alerting/` directory (this one)

 1. `script.sh` -> Absolute path of the `alerting.conf` file in your Hyprland configuration;
 2. `reference.sh` -> Absolute path of the `script.sh` script;
 3. `systemd/alerting.service` -> Absolute path of the `reference.sh` script.
 3. `udev/alerting.rules` -> Absolute path of the `reference.sh` script.

If you are wondering where to see these files, type `ls`.

### Configuring Periodic/Event Calls

There are two ways to run this script automatically: using udev or using systemd. I've ran into some problems with udev, but if you get it working, it's undoubtedly the better option.

Systemd is used to call the script periodically on distinct time intervals (like every minute), while udev is used to call the script when the battery percentage changes. I would recommend you try to use udev first, and if you don't get it working, switch to systemd.

#### Setting up *udev*

*udev* generally works in this way: it triggers events based on actions done using rules. These rules should be located in the `/etc/udev/rules.d/` directory.

There is already a rule written for this stored in the `udev` folder, but I did not get it working as events were not getting called most of the time. You can simply move it with this command: `sudo mv udev/alerting.rules /etc/udev/rules.d/`. Then you can reload your udev rules with this command: `sudo udevadm control --reload-rules`.

#### Setting up *systemd*

*systemd* works with services that I will not try to explain as I do not know enough about it. Services are located in the `/etc/systemd/system` directory.

There is already a service that works on a timer stored in the `systemd` folder. You can simply move it with this command: `sudo mv systemd/* /etc/systemd/system/`. Then you can reload services using this command: `sudo systemctl daemon-reload`; you can enable your timer with this command: `sudo systemctl enable alerting.timer`; you can directly start the timer with this command: `sudo systemctl start alerting.timer`. Later you can use `sudo systemctl status alerting.timer` to get information about the timer. Once the timer is started, you can use `sudo systemctl list-timers` to see how much time there is left until the next call.

## How to Program Functions

TODO
