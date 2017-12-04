#!/bin/bash
#!/bin/bash
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd -P`
popd > /dev/null

sudo ln -s -f  $SCRIPTPATH/midi2osc.service /etc/systemd/system/midi2osc.service

sudo systemctl daemon-reload
sudo systemctl start midi2osc.service
