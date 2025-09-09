#line 2 "src/Gui/AccountRegister/DelegateSuggestion.cpp"

#include <Wt/WSuggestionPopup.h>
#include <Wt/WDateTime.h>

#include "Editor.h"
#include "DelegateSuggestion.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */


GCW::Gui::AccountRegister::DelegateSuggestion::
DelegateSuggestion( Editor * _editor )
: DelegateBase( _editor )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegister::DelegateSuggestion::
~DelegateSuggestion()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegister::DelegateSuggestion::
createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "(): " << _index.row() << "," << _index.column()
    << " SuggestionDelegate::" << __FUNCTION__
    << " '" << Wt::asString( _index.data( Wt::ItemDataRole::Edit ) ) << "'"
    << std::endl;
#endif

  auto retVal = DelegateBase::createEditor( _index, _flags );
  auto cw = dynamic_cast< Wt::WContainerWidget* >( retVal.get() );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >( cw-> widget(0) );

  if( false /* lineEdit */ )
  {
    // options for email address suggestions
    Wt::WSuggestionPopup::Options popupOptions =
    {
      "<b>",                // highlightBeginTag
      "</b>",               // highlightEndTag
      ',',                  // listSeparator      (for multiple addresses)
      " \n",                // whitespace
      "()[]{}-., \"@\n;:",  // wordSeparators     (within an address)
      ""                    // appendReplacedText (prepare next email address)
     };

    auto popup = retVal-> addChild( std::make_unique< Wt::WSuggestionPopup >( popupOptions ) );
    popup-> forEdit( lineEdit );

//    auto batchEditModel  = dynamic_cast< const Wt::WBatchEditProxyModel*             >( _index.model() );
//    auto sortFilterModel = dynamic_cast< const Wt::WSortFilterProxyModel*            >( _index.model() );;
//    auto baseModel       = dynamic_cast< const GCW::Gui::AccountRegister::BaseModel* >( sortFilterModel-> sourceModel().get() );
    auto baseModel       = dynamic_cast< const GCW::Gui::AccountRegister::Model* >( _index.model() );

    for( auto item : baseModel-> suggestionsFromColumn( _index.column() ) )
      popup-> addSuggestion( item, item );
  }

  return retVal;

} // endcreateEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >



