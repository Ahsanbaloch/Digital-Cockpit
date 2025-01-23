

# Docker compose command
DOCKER_COMPOSE := docker-compose

all: run

run:
	xhost +local:docker
	gnome-terminal -- bash -c "make speed_feeder; exec bash" &
	gnome-terminal -- bash -c "make someip_server; exec bash" &
# $(MAKE) -j2 speed_feeder someip_server

speed_feeder:
	$(DOCKER_COMPOSE) build speed_feeder
	$(DOCKER_COMPOSE) run --rm -it speed_feeder
	docker exec -it $$(docker-compose ps -q speed_feeder) bash

someip_server:
	$(DOCKER_COMPOSE) build someip_server
	$(DOCKER_COMPOSE) up someip_server
	docker exec -it $$(docker-compose ps -q someip_server) bash

clean:
	$(DOCKER_COMPOSE) down

fclean: clean
	$(DOCKER_COMPOSE) down -v --rmi all --remove-orphans

.PHONY: all run clean fclean speed_feeder someip_server
