#pragma once
#include <SFML/Graphics.hpp>


class FocusObject
{
public:
    virtual void setFocus() = 0;
    virtual void deleteFocus() = 0;
    virtual void event(const sf::Event&) = 0;
};



class TextBox : public sf::Drawable, public FocusObject , public sf::Transformable 
{
public:
    TextBox(const sf::Text& text);
    virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
    virtual void setFocus();
    virtual void deleteFocus();
    virtual void event(const sf::Event& event);
    void setText(const sf::String& str);
    sf::String getText();
private:
    void updateRect();
    mutable sf::RectangleShape m_box;
    mutable sf::Text m_text;
    mutable sf::String m_newText;
    mutable bool m_textChanged;
};



class FocusController
{
public:
    FocusController(FocusObject* obj = 0);
    void setFocusObject(FocusObject* new_obj);
    FocusObject* getFocusObject();

private:
    FocusObject* m_object;
};
