#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
  Vector pos;
  Vector vel;
  int size;
  float angle;
  int points_len;
  Vector *points;
} Ship;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  Ship *ship;
  int is_running;
} State;

void quit(State *state) {
  if (state->window != NULL) {
    SDL_DestroyWindow(state->window);
  }

  if (state->renderer != NULL) {
    SDL_DestroyRenderer(state->renderer);
  }

  SDL_Quit();
}

State state = {};

void handle_event(State *state, SDL_Event *event) {
  Vector v = create_vector(0, 0);
  switch (event->key.keysym.sym) {
  case SDLK_d:
    state->ship->angle += 10;
    break;
  case SDLK_a:
    state->ship->angle -= 10;
    break;
  case SDLK_w:
    v.y = -1;
    break;
  case SDLK_s:
    if (v.y > 0)
      v.y = 10;
    break;
  case SDLK_q:
    state->is_running = 0;
    break;
  }

  state->ship->vel = add_vector(state->ship->vel, v);
}

void update(Ship *ship) {
  const float ACCELERATION = 0.1f;
  const float FRICTION = 0.99f;
  const float MAX_SPEED = 5.0f;

  ship->pos = create_vector(fmod(ship->pos.x, WINDOW_WIDTH),
                            fmod(ship->pos.y, WINDOW_HEIGHT));
  ship->pos = add_vector(ship->pos, rotate_vector(ship->vel, ship->angle));
}

void draw_ship(State *state) {
  int SCALE = 5;
  int size = state->ship->points_len;
  Vector *pos = state->ship->points;

  Vector v1 = {};
  Vector v2 = {};
  for (int i = 0; i < size; i++) {
    int next = (i + 1) % size;

    v1 = add_vector(
        state->ship->pos,
        scale_vector(rotate_vector(pos[i], state->ship->angle), SCALE));
    v2 = add_vector(
        state->ship->pos,
        scale_vector(rotate_vector(pos[next], state->ship->angle), SCALE));

    SDL_RenderDrawLine(state->renderer, v1.x, v1.y, v2.x, v2.y);
  }
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Erro ao inicializar a SDL: %s\n", SDL_GetError());
    return 1;
  }

  Vector ship_points[5] = {
      create_vector(0, -5), create_vector(4, 5),  create_vector(2, 3),
      create_vector(-2, 3), create_vector(-4, 5),
  };

  Ship ship = {};
  ship.pos = create_vector(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  ship.vel = create_vector(0, 0);
  ship.size = 50;
  ship.points_len = 5;
  ship.points = ship_points;

  state.ship = &ship;
  state.is_running = 1;
  state.window = SDL_CreateWindow("Learning SDL", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  state.renderer =
      SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Event event;

  // SDL_RenderSetLogicalSize(state.renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

  while (state.is_running) {
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
      printf("quiting\n");
      state.is_running = 0;
    }

    handle_event(&state, &event);

    update(&ship);

    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);

    SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
    draw_ship(&state);

    SDL_RenderPresent(state.renderer);
    SDL_Delay(16);
  }

  quit(&state);

  return 0;
}
