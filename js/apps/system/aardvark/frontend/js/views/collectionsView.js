/*jslint indent: 2, nomen: true, maxlen: 100, sloppy: true, vars: true, white: true, plusplus: true */
/*global Backbone, templateEngine, window, setTimeout, clearTimeout, arangoHelper, $*/

var collectionsView = Backbone.View.extend({
  el: '#content',
  /*el2: '.thumbnails',*/
  el2: '#collectionsThumbnailsIn',

  searchTimeout: null,

  initialize: function () {
  },

  template: templateEngine.createTemplate("collectionsView.ejs"),

  render: function () {
    var dropdownVisible = false; 
    if ($('#collectionsDropdown').is(':visible')) {
      dropdownVisible = true;
    }

    $(this.el).html(this.template.text);
    this.setFilterValues();

    if (dropdownVisible === true) {
      $('#collectionsDropdown2').show();
    }

    var searchOptions = this.collection.searchOptions;

    $('#collectionsThumbnailsIn', this.el).append(
      '<li class="span3"><a href="#new" class="add">' +
      '<span id="newCollection" class="pull-left glyphicon glyphicon-plus-sign" />' +
      'Add Collection</a></li>'
    );

    this.collection.getFiltered(searchOptions).forEach(function (arango_collection) {
      $('#collectionsThumbnailsIn', this.el).append(new window.CollectionListItemView({
        model: arango_collection
      }).render().el);
    }, this);

    //append info icon for loaded collections
    $('.loaded').parent().prev().append(
      '<span class="glyphicon glyphicon-info-sign spanInfo ICON" ' + 
      'title="Show collection properties"</span>'
    );
    $('.unloaded').parent().prev().append(
      '<span class="glyphicon glyphicon-info-sign spanDisabled ICON" alt="disabled"</span>'
    );

    $('#searchInput').val(searchOptions.searchPhrase);
    $('#searchInput').focus();
    var val = $('#searchInput').val();
    $('#searchInput').val('');
    $('#searchInput').val(val);

    arangoHelper.fixTooltips(".glyphicon, .arangoicon", "left");

    return this;
  },
  events: {
    "keydown #searchInput" : "restrictToSearchPhraseKey",
    "change #searchInput"   : "restrictToSearchPhrase",
    "click #searchSubmit"   : "restrictToSearchPhrase",
    "click #checkSystem"    : "checkSystem",
    "click #checkLoaded"    : "checkLoaded",
    "click #checkUnloaded"  : "checkUnloaded",
    "click #checkDocument"  : "checkDocument",
    "click #checkEdge"      : "checkEdge",
    "click #sortName"       : "sortName",
    "click #sortType"       : "sortType",
    "click #sortOrder"      : "sortOrder",
    "click #collectionsToggle"     : "toggleView",
    "click #transparentHeader .btn-group .dropdown-toggle" : "slideEffect"
  },

  toggleView: function() {
    $('#collectionsDropdown2').slideToggle(200);
  },

  checkSystem: function () {
    var searchOptions = this.collection.searchOptions;
    var oldValue = searchOptions.includeSystem;

    searchOptions.includeSystem = ($('#checkSystem').is(":checked") === true);

    if (oldValue !== searchOptions.includeSystem) {
      this.render();
    }
  },
  checkEdge: function () {
    var searchOptions = this.collection.searchOptions;
    var oldValue = searchOptions.includeEdge;

    searchOptions.includeEdge = ($('#checkEdge').is(":checked") === true);

    if (oldValue !== searchOptions.includeEdge) {
      this.render();
    }
  },
  checkDocument: function () {
    var searchOptions = this.collection.searchOptions;
    var oldValue = searchOptions.includeDocument;

    searchOptions.includeDocument = ($('#checkDocument').is(":checked") === true);

    if (oldValue !== searchOptions.includeDocument) {
      this.render();
    }
  },
  checkLoaded: function () {
    var searchOptions = this.collection.searchOptions;
    var oldValue = searchOptions.includeLoaded;

    searchOptions.includeLoaded = ($('#checkLoaded').is(":checked") === true);

    if (oldValue !== searchOptions.includeLoaded) {
      this.render();
    }
  },
  checkUnloaded: function () {
    var searchOptions = this.collection.searchOptions;
    var oldValue = searchOptions.includeUnloaded;

    searchOptions.includeUnloaded = ($('#checkUnloaded').is(":checked") === true);

    if (oldValue !== searchOptions.includeUnloaded) {
      this.render();
    }
  },
  sortName: function () {
    var searchOptions = this.collection.searchOptions;
    var oldValue = searchOptions.sortBy;

    searchOptions.sortBy = (($('#sortName').is(":checked") === true) ? 'name' : 'type');

    if (oldValue !== searchOptions.sortBy) {
      this.render();
    }
  },
  sortType: function () {
    var searchOptions = this.collection.searchOptions;
    var oldValue = searchOptions.sortBy;

    searchOptions.sortBy = (($('#sortType').is(":checked") === true) ? 'type' : 'name');

    if (oldValue !== searchOptions.sortBy) {
      this.render();
    }
  },
  sortOrder: function () {
    var searchOptions = this.collection.searchOptions;
    var oldValue = searchOptions.sortOrder;

    searchOptions.sortOrder = (($('#sortOrder').is(":checked") === true) ? -1 : 1);

    if (oldValue !== searchOptions.sortOrder) {
      this.render();
    }
  },

  setFilterValues: function () {
    var searchOptions = this.collection.searchOptions;
    $('#checkLoaded').attr('checked', searchOptions.includeLoaded);
    $('#checkUnloaded').attr('checked', searchOptions.includeUnloaded);
    $('#checkSystem').attr('checked', searchOptions.includeSystem);
    $('#checkEdge').attr('checked', searchOptions.includeEdge);
    $('#checkDocument').attr('checked', searchOptions.includeDocument);
    $('#sortName').attr('checked', searchOptions.sortBy !== 'type');
    $('#sortType').attr('checked', searchOptions.sortBy === 'type');
    $('#sortOrder').attr('checked', searchOptions.sortOrder !== 1);
  },

  search: function () {
    var searchOptions = this.collection.searchOptions;
    var searchPhrase = $('#searchInput').val();

    if (searchPhrase === searchOptions.searchPhrase) {
      return;
    }
    searchOptions.searchPhrase = searchPhrase;

    this.render();
  },

  resetSearch: function () {
    if (this.searchTimeout) {
      clearTimeout(this.searchTimeout);
      this.searchTimeout = null;
    }
    
    var searchOptions = this.collection.searchOptions;
    searchOptions.searchPhrase = null;
  },

  restrictToSearchPhraseKey: function (e) {
    // key pressed in search box
    var self = this;
    
    // force a new a search
    this.resetSearch();

    self.searchTimeout = setTimeout(function (){
      self.search();
    }, 200);
  },

  restrictToSearchPhrase: function () {
    // force a new a search
    this.resetSearch();

    // search executed
    this.search();
  }

});
