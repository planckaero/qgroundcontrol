cd libs/mavlink
python -m virtualenv --no-site-packages env
source env/bin/activate
cd pymavlink
pip install -r requirements.txt
python setup.py install
cd ..
mkdir ../mavlink_generated
python -m pymavlink.tools.mavgen --lang C --wire-protocol 2.0 message_definitions/v1.0/ardupilotmega.xml -o ../mavlink_generated
deactivate
rm -rf env
cd ../..
