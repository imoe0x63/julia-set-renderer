
#ifndef MAIN_HPP
#define MAIN_HPP

#include <SFML/Graphics.hpp>

namespace m {

	struct renderer : public sf::RenderWindow {
		renderer(std::string_view title, const sf::VideoMode& vm = { 640, 460 }) :
			event({}),
			RenderWindow(vm, title.data())
			
		{
			texture.create(vm.width , vm.height );
			sprite.setTexture(texture);

			if (!shader.loadFromFile("assets/frag.glsl", sf::Shader::Fragment)) {
				printf("failed to load shader\n");
			}
			shader.setUniform("resolution", sf::Vector2f(float(vm.width), float(vm.height)));
		}

		int exec() {

			
			sf::Time delta = sf::Time::Zero;

			clock.restart();
			while (isOpen()) {
				delta = clock.restart();
				
				handle_evets();

				update(delta);
				render();
			}
			return 0;
		}

	private:

		void handle_evets() {
			while (pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					close();
				}

				if (event.KeyPressed) {
					if (event.key.code == sf::Keyboard::S) {
						texture.copyToImage().saveToFile("assets/image.png");
					}
				}
			}
		}
		void update(const sf::Time& delta) {
			setTitle(" fps : " + std::to_string(delta.asSeconds()));


			sf::Vector2i m = sf::Mouse::getPosition(*this);
			sf::Vector2f mouse = sf::Vector2f(float(m.x), float(m.y));

			shader.setUniform("mouse", mouse);

		}
		void render() {
			clear(sf::Color::Black);

			
			if(shader.isAvailable())
				draw(sprite, &shader);
			else {
				draw(sprite);
			}
			display();
		}

	private:
		const sf::Time  time_per_frame = sf::seconds(1.f / 60.f);
		
		sf::Texture texture;
		sf::Sprite  sprite;
		sf::Shader	shader;

		sf::Event	event;
		sf::Clock	clock;
	};
}

#endif//