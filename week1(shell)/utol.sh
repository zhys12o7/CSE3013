#!/bin/bash

echo 'Working directory' 
read dirname



if [ -n "$dirname" ]
then
        if [ -d $dirname ]
        then
                if [ -x $dirname ]
                then
                        if [ -w $dirname ]
                        then
                                if [ -r $dirname ]
                                then
                                        cd $dirname
                                        for dir in *
                                        do
                                        newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
                                        mv $dir $newname
                                        done

                                else
                                        echo "permission denied -r"
                                fi
                        else
                                echo "permission denied -r"
                        fi
                else
                        echo "permission denied -x"
                fi
        else
                echo "wrong directory"
        fi

else

        for dir in *
        do
        newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
        mv $dir $newname
        done
fi


