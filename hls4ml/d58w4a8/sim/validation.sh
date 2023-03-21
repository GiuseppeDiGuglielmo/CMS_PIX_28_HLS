HW='d58w4a8'
LOG_DIR=log


echo "INFO: Hardware implementation: $HW"

for l in `seq 0 11`; do
    ACCURACY_LOG=accuracy_y_local_$l.log
    rm -f $ACCURACY_LOG
    for i in `seq 0 9`; do
        echo "INFO: --------------------------------------"
        echo "INFO: y-local $l, iter $i"
        RUN_LOG=run.log

        rm -f tb_data/tb_input_features.dat
        cd tb_data && ln -s ../../../tb_txt/pad/l$l/tb_input_features.dat && cd ..
        rm -f tb_data/tb_output_predictions.dat
        cd tb_data && ln -s ../../../tb_txt/pad/l$l/tb_output_predictions.dat && cd ..

        rm -f weights/w2.txt
        ln -s ../../../../weights_txt/$HW/y_local_$l/iter_$i/w2.txt weights/w2.txt
        rm -f weights/b2.txt
        ln -s ../../../../weights_txt/$HW/y_local_$l/iter_$i/b2.txt weights/b2.txt

        rm -f weights/w5.txt
        ln -s ../../../../weights_txt/$HW/y_local_$l/iter_$i/w5.txt weights/w5.txt
        rm -f weights/b5.txt
        ln -s ../../../../weights_txt/$HW/y_local_$l/iter_$i/b5.txt weights/b5.txt

        make clean
        make -j run | tee $RUN_LOG
        grep Accuracy run.log | awk '{ print $3 }'>> $ACCURACY_LOG
    done
done

python validation.py

mv hw_accuracy.csv $HW\_hw_accuracy.csv
mkdir -p $LOG_DIR
mv accuracy*.log $LOG_DIR

echo "INFO: done ($HW)"

