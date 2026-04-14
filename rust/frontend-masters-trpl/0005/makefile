run:
	cargo run

watch:
	make run && \
	fswatch -o ./src | xargs -n1 -I {} make run;
