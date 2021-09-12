if [ $# -eq 1 ]
  	then
    	make -C old_philosophers/philo_one $1
		make -C old_philosophers/philo_two $1
		make -C old_philosophers/philo_three $1
	else
		make -C old_philosophers/philo_one
		make -C old_philosophers/philo_two
		make -C old_philosophers/philo_three
fi