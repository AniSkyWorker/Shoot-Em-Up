#include "SettingsState.h"
#include "ResourceHolder.h"
#include "KeyboardKeys.h"

SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
	, GUI_container()
{
	background_sprite.setTexture(context.textures->get(Textures::TitleScreen));

	addButtonLabel(Player::MoveLeft, 300.f, "Move Left", context);
	addButtonLabel(Player::MoveRight, 350.f, "Move Right", context);
	addButtonLabel(Player::MoveUp, 400.f, "Move Up", context);
	addButtonLabel(Player::MoveDown, 450.f, "Move Down", context);
	addButtonLabel(Player::Fire, 500.f, "Fire", context);
	addButtonLabel(Player::LaunchMissile, 550.f, "Missile", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(80.f, 620.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	GUI_container.pack(backButton);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(background_sprite);
	window.draw(GUI_container);
}

bool SettingsState::update(sf::Time)
{
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;

	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{
		if (binding_buttons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().player->assignKey(static_cast<Player::Action>(action), event.key.code);
				binding_buttons[action]->deactivate();
			}
			break;
		}
	}

	if (isKeyBinding)
		updateLabels();
	else
		GUI_container.handleEvent(event);

	return false;
}

void SettingsState::updateLabels()
{
	Player& player = *getContext().player;

	for (std::size_t i = 0; i < Player::ActionCount; ++i)
	{
		sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
		binding_labels[i]->setText(KeyboardKeys::getKeyName(key));
	}
}

void SettingsState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	binding_buttons[action] = std::make_shared<GUI::Button>(context);
	binding_buttons[action]->setPosition(80.f, y);
	binding_buttons[action]->setText(text);
	binding_buttons[action]->setToggle(true);

	binding_labels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	binding_labels[action]->setPosition(300.f, y + 15.f);

	GUI_container.pack(binding_buttons[action]);
	GUI_container.pack(binding_labels[action]);
}
