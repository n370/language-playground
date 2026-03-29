module:
	FOLDER_NAME=$$(echo "$(MODULE_NAME)" | sed -e 's/[\/\.]/-/g'); \
	mkdir $$FOLDER_NAME; \
	cd $$FOLDER_NAME; \
	go mod init $(MODULE_NAME); \
	echo "package main\n\nfunc main() {\n\t\n}\n" > main.go; \
	echo "run:\n\tgo run ." > makefile;
