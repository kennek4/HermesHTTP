#!/bin/bash

ip=${1:-localhost}
port=${2-8080}

for i in {1..5000}; do
    echo "Client #$i"
    time curl "$ip":"$port"
done
