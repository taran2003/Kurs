#include "text_box.h"

TextBox::TextBox(const sf::Text& text) : m_text(text)
    {
        m_newText = m_text.getString();
        updateRect();
        m_box.setFillColor(sf::Color::White);
    }

void TextBox::draw(sf::RenderTarget& render, sf::RenderStates states) const
{
    if (m_textChanged)
    {
        const_cast<TextBox*>(this)->setText(m_newText);

        m_textChanged = false;
    }
    render.draw(m_box, states);
    render.draw(m_text, states);
}

void TextBox::setFocus()
{
    m_box.setFillColor(sf::Color::Black);
}

void TextBox::deleteFocus()
{
    m_box.setFillColor(sf::Color::Blue);
}

void TextBox::event(const sf::Event& event)
{
    if (event.type == sf::Event::TextEntered)
    {
        //Обработка ввода
        m_textChanged = true;
        switch (event.text.unicode)
        {
        case 0xD: //Return
            m_newText += L'\n';
            break;
        case 0x8://Backspace
            if (!m_newText.isEmpty())
                m_newText.erase(m_newText.getSize() - 1);
            break;
        default:
        {
            m_newText += static_cast<wchar_t>(event.text.unicode);
        }
        }
    }
}

void TextBox::setText(const sf::String& str)
{
    m_text.setString(str);
    updateRect();
}

sf::String TextBox::getText()
{
    return m_newText;
}

void TextBox::updateRect()
{
    sf::FloatRect rect = m_text.getGlobalBounds();
    m_box.setPosition(rect.left - 5, rect.top - 5);
    m_box.setSize(sf::Vector2f(rect.width + 10, rect.height + 10));
}

FocusController::FocusController(FocusObject* obj) : m_object(obj)
{
    if (m_object != 0)
    {
        m_object->setFocus();
    }
}

void FocusController::setFocusObject(FocusObject* new_obj)
{
    if (m_object == new_obj)
        return;
    if (m_object != 0)
        m_object->deleteFocus();
    if (new_obj != 0)
        new_obj->setFocus();
    m_object = new_obj;

}

FocusObject* FocusController::getFocusObject()
{
    return m_object;
}
