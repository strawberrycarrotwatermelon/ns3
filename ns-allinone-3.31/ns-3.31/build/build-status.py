#! /usr/bin/env python3

# Programs that are runnable.
ns3_runnable_programs = ['build/src/aodv/examples/ns3.31-aodv-debug', 'build/src/applications/examples/ns3.31-three-gpp-http-example-debug', 'build/src/bridge/examples/ns3.31-csma-bridge-debug', 'build/src/bridge/examples/ns3.31-csma-bridge-one-hop-debug', 'build/src/buildings/examples/ns3.31-buildings-pathloss-profiler-debug', 'build/src/buildings/examples/ns3.31-outdoor-random-walk-example-debug', 'build/src/config-store/examples/ns3.31-config-store-save-debug', 'build/src/core/examples/ns3.31-main-callback-debug', 'build/src/core/examples/ns3.31-sample-simulator-debug', 'build/src/core/examples/ns3.31-main-ptr-debug', 'build/src/core/examples/ns3.31-main-random-variable-stream-debug', 'build/src/core/examples/ns3.31-sample-random-variable-debug', 'build/src/core/examples/ns3.31-sample-random-variable-stream-debug', 'build/src/core/examples/ns3.31-command-line-example-debug', 'build/src/core/examples/ns3.31-hash-example-debug', 'build/src/core/examples/ns3.31-sample-log-time-format-debug', 'build/src/core/examples/ns3.31-test-string-value-formatting-debug', 'build/src/core/examples/ns3.31-sample-show-progress-debug', 'build/src/core/examples/ns3.31-empirical-random-variable-example-debug', 'build/src/core/examples/ns3.31-system-path-examples-debug', 'build/src/core/examples/ns3.31-main-test-sync-debug', 'build/src/csma/examples/ns3.31-csma-one-subnet-debug', 'build/src/csma/examples/ns3.31-csma-broadcast-debug', 'build/src/csma/examples/ns3.31-csma-packet-socket-debug', 'build/src/csma/examples/ns3.31-csma-multicast-debug', 'build/src/csma/examples/ns3.31-csma-raw-ip-socket-debug', 'build/src/csma/examples/ns3.31-csma-ping-debug', 'build/src/csma-layout/examples/ns3.31-csma-star-debug', 'build/src/dsdv/examples/ns3.31-dsdv-manet-debug', 'build/src/dsr/examples/ns3.31-dsr-debug', 'build/src/energy/examples/ns3.31-li-ion-energy-source-debug', 'build/src/energy/examples/ns3.31-rv-battery-model-test-debug', 'build/src/energy/examples/ns3.31-basic-energy-model-test-debug', 'build/src/fd-net-device/examples/ns3.31-dummy-network-debug', 'build/src/fd-net-device/examples/ns3.31-fd2fd-onoff-debug', 'build/src/fd-net-device/examples/ns3.31-realtime-dummy-network-debug', 'build/src/fd-net-device/examples/ns3.31-realtime-fd2fd-onoff-debug', 'build/src/fd-net-device/examples/ns3.31-fd-emu-ping-debug', 'build/src/fd-net-device/examples/ns3.31-fd-emu-udp-echo-debug', 'build/src/fd-net-device/examples/ns3.31-fd-emu-onoff-debug', 'build/src/fd-net-device/examples/ns3.31-fd-tap-ping-debug', 'build/src/fd-net-device/examples/ns3.31-fd-tap-ping6-debug', 'build/src/internet/examples/ns3.31-main-simple-debug', 'build/src/internet-apps/examples/ns3.31-dhcp-example-debug', 'build/src/internet-apps/examples/ns3.31-traceroute-example-debug', 'build/src/lr-wpan/examples/ns3.31-lr-wpan-packet-print-debug', 'build/src/lr-wpan/examples/ns3.31-lr-wpan-phy-test-debug', 'build/src/lr-wpan/examples/ns3.31-lr-wpan-data-debug', 'build/src/lr-wpan/examples/ns3.31-lr-wpan-error-model-plot-debug', 'build/src/lr-wpan/examples/ns3.31-lr-wpan-error-distance-plot-debug', 'build/src/lr-wpan/examples/ns3.31-lr-wpan-mlme-debug', 'build/src/lte/examples/ns3.31-lena-cqi-threshold-debug', 'build/src/lte/examples/ns3.31-lena-dual-stripe-debug', 'build/src/lte/examples/ns3.31-lena-fading-debug', 'build/src/lte/examples/ns3.31-lena-intercell-interference-debug', 'build/src/lte/examples/ns3.31-lena-ipv6-addr-conf-debug', 'build/src/lte/examples/ns3.31-lena-ipv6-ue-rh-debug', 'build/src/lte/examples/ns3.31-lena-ipv6-ue-ue-debug', 'build/src/lte/examples/ns3.31-lena-pathloss-traces-debug', 'build/src/lte/examples/ns3.31-lena-profiling-debug', 'build/src/lte/examples/ns3.31-lena-rem-debug', 'build/src/lte/examples/ns3.31-lena-rem-sector-antenna-debug', 'build/src/lte/examples/ns3.31-lena-rlc-traces-debug', 'build/src/lte/examples/ns3.31-lena-simple-debug', 'build/src/lte/examples/ns3.31-lena-simple-epc-debug', 'build/src/lte/examples/ns3.31-lena-simple-epc-backhaul-debug', 'build/src/lte/examples/ns3.31-lena-deactivate-bearer-debug', 'build/src/lte/examples/ns3.31-lena-x2-handover-debug', 'build/src/lte/examples/ns3.31-lena-x2-handover-measures-debug', 'build/src/lte/examples/ns3.31-lena-frequency-reuse-debug', 'build/src/lte/examples/ns3.31-lena-distributed-ffr-debug', 'build/src/lte/examples/ns3.31-lena-uplink-power-control-debug', 'build/src/lte/examples/ns3.31-lena-radio-link-failure-debug', 'build/src/lte/examples/ns3.31-lena-simple-epc-emu-debug', 'build/src/mesh/examples/ns3.31-mesh-debug', 'build/src/mobility/examples/ns3.31-main-grid-topology-debug', 'build/src/mobility/examples/ns3.31-main-random-topology-debug', 'build/src/mobility/examples/ns3.31-main-random-walk-debug', 'build/src/mobility/examples/ns3.31-mobility-trace-example-debug', 'build/src/mobility/examples/ns3.31-ns2-mobility-trace-debug', 'build/src/mobility/examples/ns3.31-bonnmotion-ns2-example-debug', 'build/src/netanim/examples/ns3.31-dumbbell-animation-debug', 'build/src/netanim/examples/ns3.31-grid-animation-debug', 'build/src/netanim/examples/ns3.31-star-animation-debug', 'build/src/netanim/examples/ns3.31-wireless-animation-debug', 'build/src/netanim/examples/ns3.31-uan-animation-debug', 'build/src/netanim/examples/ns3.31-colors-link-description-debug', 'build/src/netanim/examples/ns3.31-resources-counters-debug', 'build/src/network/examples/ns3.31-main-packet-header-debug', 'build/src/network/examples/ns3.31-main-packet-tag-debug', 'build/src/network/examples/ns3.31-packet-socket-apps-debug', 'build/src/nix-vector-routing/examples/ns3.31-nix-simple-debug', 'build/src/nix-vector-routing/examples/ns3.31-nms-p2p-nix-debug', 'build/src/olsr/examples/ns3.31-simple-point-to-point-olsr-debug', 'build/src/olsr/examples/ns3.31-olsr-hna-debug', 'build/src/point-to-point/examples/ns3.31-main-attribute-value-debug', 'build/src/propagation/examples/ns3.31-main-propagation-loss-debug', 'build/src/propagation/examples/ns3.31-jakes-propagation-model-example-debug', 'build/src/sixlowpan/examples/ns3.31-example-sixlowpan-debug', 'build/src/sixlowpan/examples/ns3.31-example-ping-lr-wpan-debug', 'build/src/sixlowpan/examples/ns3.31-example-ping-lr-wpan-beacon-debug', 'build/src/sixlowpan/examples/ns3.31-example-ping-lr-wpan-mesh-under-debug', 'build/src/spectrum/examples/ns3.31-adhoc-aloha-ideal-phy-debug', 'build/src/spectrum/examples/ns3.31-adhoc-aloha-ideal-phy-matrix-propagation-loss-model-debug', 'build/src/spectrum/examples/ns3.31-adhoc-aloha-ideal-phy-with-microwave-oven-debug', 'build/src/spectrum/examples/ns3.31-tv-trans-example-debug', 'build/src/spectrum/examples/ns3.31-tv-trans-regional-example-debug', 'build/src/spectrum/examples/ns3.31-three-gpp-channel-example-debug', 'build/src/stats/examples/ns3.31-gnuplot-example-debug', 'build/src/stats/examples/ns3.31-double-probe-example-debug', 'build/src/stats/examples/ns3.31-time-probe-example-debug', 'build/src/stats/examples/ns3.31-gnuplot-aggregator-example-debug', 'build/src/stats/examples/ns3.31-gnuplot-helper-example-debug', 'build/src/stats/examples/ns3.31-file-aggregator-example-debug', 'build/src/stats/examples/ns3.31-file-helper-example-debug', 'build/src/tap-bridge/examples/ns3.31-tap-csma-debug', 'build/src/tap-bridge/examples/ns3.31-tap-csma-virtual-machine-debug', 'build/src/tap-bridge/examples/ns3.31-tap-wifi-virtual-machine-debug', 'build/src/tap-bridge/examples/ns3.31-tap-wifi-dumbbell-debug', 'build/src/topology-read/examples/ns3.31-topology-example-sim-debug', 'build/src/traffic-control/examples/ns3.31-red-tests-debug', 'build/src/traffic-control/examples/ns3.31-red-vs-ared-debug', 'build/src/traffic-control/examples/ns3.31-adaptive-red-tests-debug', 'build/src/traffic-control/examples/ns3.31-pfifo-vs-red-debug', 'build/src/traffic-control/examples/ns3.31-codel-vs-pfifo-basic-test-debug', 'build/src/traffic-control/examples/ns3.31-codel-vs-pfifo-asymmetric-debug', 'build/src/traffic-control/examples/ns3.31-pie-example-debug', 'build/src/uan/examples/ns3.31-uan-cw-example-debug', 'build/src/uan/examples/ns3.31-uan-rc-example-debug', 'build/src/uan/examples/ns3.31-uan-raw-example-debug', 'build/src/uan/examples/ns3.31-uan-ipv4-example-debug', 'build/src/uan/examples/ns3.31-uan-ipv6-example-debug', 'build/src/uan/examples/ns3.31-uan-6lowpan-example-debug', 'build/src/virtual-net-device/examples/ns3.31-virtual-net-device-debug', 'build/src/wave/examples/ns3.31-wave-simple-80211p-debug', 'build/src/wave/examples/ns3.31-wave-simple-device-debug', 'build/src/wave/examples/ns3.31-vanet-routing-compare-debug', 'build/src/wifi/examples/ns3.31-wifi-phy-test-debug', 'build/src/wifi/examples/ns3.31-wifi-test-interference-helper-debug', 'build/src/wifi/examples/ns3.31-wifi-manager-example-debug', 'build/src/wifi/examples/ns3.31-wifi-trans-example-debug', 'build/src/wifi/examples/ns3.31-wifi-phy-configuration-debug', 'build/src/wifi/examples/ns3.31-wifi-bianchi-debug', 'build/src/wimax/examples/ns3.31-wimax-ipv4-debug', 'build/src/wimax/examples/ns3.31-wimax-multicast-debug', 'build/src/wimax/examples/ns3.31-wimax-simple-debug', 'build/examples/energy/ns3.31-energy-model-example-debug', 'build/examples/energy/ns3.31-energy-model-with-harvesting-example-debug', 'build/examples/naming/ns3.31-object-names-debug', 'build/examples/routing/ns3.31-dynamic-global-routing-debug', 'build/examples/routing/ns3.31-static-routing-slash32-debug', 'build/examples/routing/ns3.31-global-routing-slash32-debug', 'build/examples/routing/ns3.31-global-injection-slash32-debug', 'build/examples/routing/ns3.31-simple-global-routing-debug', 'build/examples/routing/ns3.31-simple-alternate-routing-debug', 'build/examples/routing/ns3.31-mixed-global-routing-debug', 'build/examples/routing/ns3.31-simple-routing-ping6-debug', 'build/examples/routing/ns3.31-manet-routing-compare-debug', 'build/examples/routing/ns3.31-ripng-simple-network-debug', 'build/examples/routing/ns3.31-rip-simple-network-debug', 'build/examples/routing/ns3.31-global-routing-multi-switch-plus-router-debug', 'build/examples/routing/ns3.31-simple-multicast-flooding-debug', 'build/examples/ipv6/ns3.31-icmpv6-redirect-debug', 'build/examples/ipv6/ns3.31-ping6-debug', 'build/examples/ipv6/ns3.31-radvd-debug', 'build/examples/ipv6/ns3.31-radvd-two-prefix-debug', 'build/examples/ipv6/ns3.31-test-ipv6-debug', 'build/examples/ipv6/ns3.31-fragmentation-ipv6-debug', 'build/examples/ipv6/ns3.31-fragmentation-ipv6-two-MTU-debug', 'build/examples/ipv6/ns3.31-loose-routing-ipv6-debug', 'build/examples/ipv6/ns3.31-wsn-ping6-debug', 'build/examples/socket/ns3.31-socket-bound-static-routing-debug', 'build/examples/socket/ns3.31-socket-bound-tcp-static-routing-debug', 'build/examples/socket/ns3.31-socket-options-ipv4-debug', 'build/examples/socket/ns3.31-socket-options-ipv6-debug', 'build/examples/udp/ns3.31-udp-echo-debug', 'build/examples/stats/ns3.31-wifi-example-sim-debug', 'build/examples/error-model/ns3.31-simple-error-model-debug', 'build/examples/wireless/ns3.31-mixed-wired-wireless-debug', 'build/examples/wireless/ns3.31-wifi-adhoc-debug', 'build/examples/wireless/ns3.31-wifi-clear-channel-cmu-debug', 'build/examples/wireless/ns3.31-wifi-ap-debug', 'build/examples/wireless/ns3.31-wifi-wired-bridging-debug', 'build/examples/wireless/ns3.31-wifi-multirate-debug', 'build/examples/wireless/ns3.31-wifi-simple-adhoc-debug', 'build/examples/wireless/ns3.31-wifi-simple-adhoc-grid-debug', 'build/examples/wireless/ns3.31-wifi-simple-infra-debug', 'build/examples/wireless/ns3.31-wifi-simple-interference-debug', 'build/examples/wireless/ns3.31-wifi-blockack-debug', 'build/examples/wireless/ns3.31-wifi-dsss-validation-debug', 'build/examples/wireless/ns3.31-wifi-ofdm-validation-debug', 'build/examples/wireless/ns3.31-wifi-ofdm-ht-validation-debug', 'build/examples/wireless/ns3.31-wifi-ofdm-vht-validation-debug', 'build/examples/wireless/ns3.31-wifi-hidden-terminal-debug', 'build/examples/wireless/ns3.31-wifi-ht-network-debug', 'build/examples/wireless/ns3.31-wifi-vht-network-debug', 'build/examples/wireless/ns3.31-wifi-timing-attributes-debug', 'build/examples/wireless/ns3.31-wifi-sleep-debug', 'build/examples/wireless/ns3.31-wifi-power-adaptation-distance-debug', 'build/examples/wireless/ns3.31-wifi-power-adaptation-interference-debug', 'build/examples/wireless/ns3.31-wifi-rate-adaptation-distance-debug', 'build/examples/wireless/ns3.31-wifi-aggregation-debug', 'build/examples/wireless/ns3.31-wifi-txop-aggregation-debug', 'build/examples/wireless/ns3.31-wifi-simple-ht-hidden-stations-debug', 'build/examples/wireless/ns3.31-wifi-80211n-mimo-debug', 'build/examples/wireless/ns3.31-wifi-mixed-network-debug', 'build/examples/wireless/ns3.31-wifi-tcp-debug', 'build/examples/wireless/ns3.31-wifi-80211e-txop-debug', 'build/examples/wireless/ns3.31-wifi-spectrum-per-example-debug', 'build/examples/wireless/ns3.31-wifi-spectrum-per-interference-debug', 'build/examples/wireless/ns3.31-wifi-spectrum-saturation-example-debug', 'build/examples/wireless/ns3.31-wifi-ofdm-he-validation-debug', 'build/examples/wireless/ns3.31-wifi-he-network-debug', 'build/examples/wireless/ns3.31-wifi-multi-tos-debug', 'build/examples/wireless/ns3.31-wifi-backward-compatibility-debug', 'build/examples/wireless/ns3.31-wifi-pcf-debug', 'build/examples/wireless/ns3.31-wifi-spatial-reuse-debug', 'build/examples/tutorial/ns3.31-hello-simulator-debug', 'build/examples/tutorial/ns3.31-first-debug', 'build/examples/tutorial/ns3.31-second-debug', 'build/examples/tutorial/ns3.31-third-debug', 'build/examples/tutorial/ns3.31-fourth-debug', 'build/examples/tutorial/ns3.31-fifth-debug', 'build/examples/tutorial/ns3.31-sixth-debug', 'build/examples/tutorial/ns3.31-seventh-debug', 'build/examples/matrix-topology/ns3.31-matrix-topology-debug', 'build/examples/realtime/ns3.31-realtime-udp-echo-debug', 'build/examples/udp-client-server/ns3.31-udp-client-server-debug', 'build/examples/udp-client-server/ns3.31-udp-trace-client-server-debug', 'build/examples/traffic-control/ns3.31-traffic-control-debug', 'build/examples/traffic-control/ns3.31-queue-discs-benchmark-debug', 'build/examples/traffic-control/ns3.31-red-vs-fengadaptive-debug', 'build/examples/traffic-control/ns3.31-red-vs-nlred-debug', 'build/examples/traffic-control/ns3.31-tbf-example-debug', 'build/examples/traffic-control/ns3.31-cobalt-vs-codel-debug', 'build/examples/tcp/ns3.31-tcp-large-transfer-debug', 'build/examples/tcp/ns3.31-tcp-nsc-lfn-debug', 'build/examples/tcp/ns3.31-tcp-nsc-zoo-debug', 'build/examples/tcp/ns3.31-tcp-star-server-debug', 'build/examples/tcp/ns3.31-star-debug', 'build/examples/tcp/ns3.31-tcp-bulk-send-debug', 'build/examples/tcp/ns3.31-tcp-pcap-nanosec-example-debug', 'build/examples/tcp/ns3.31-tcp-nsc-comparison-debug', 'build/examples/tcp/ns3.31-tcp-variants-comparison-debug', 'build/examples/tcp/ns3.31-tcp-pacing-debug', 'build/examples/tcp/ns3.31-dctcp-example-debug', 'build/scratch/subdir/ns3.31-subdir-debug', 'build/scratch/ns3.31-scratch-simulator-debug']

# Scripts that are runnable.
ns3_runnable_scripts = ['csma-bridge.py', 'sample-simulator.py', 'wifi-olsr-flowmon.py', 'tap-csma-virtual-machine.py', 'tap-wifi-virtual-machine.py', 'simple-routing-ping6.py', 'mixed-wired-wireless.py', 'wifi-ap.py', 'first.py', 'second.py', 'third.py', 'realtime-udp-echo.py']

