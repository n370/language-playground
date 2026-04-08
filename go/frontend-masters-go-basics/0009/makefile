run:
	go run .

watch:
	make run & \
	sleep 1; \
	PROCESS_ID=$$(ps aux | grep -e "0009$$" | awk '{print $$2}'); \
	fswatch . | while read f; do \
		kill -9 $$PROCESS_ID; \
		make run & \
		sleep 1; \
		PROCESS_ID=$$(ps aux | grep -e "0009$$" | awk '{print $$2}'); \
	done;
