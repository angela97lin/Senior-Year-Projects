// Before any routing run the requireLogin function except home page
Router.plugin('ensureSignedIn', {
  only: ['projectPage', 'folderPage', 'postPage', 'profilePage']
});
Router.configure({
  layoutTemplate: 'layout',
  yieldTemplates: {
    header: {to: 'header'}
  },
  notFoundTemplate: 'notFound'
});

Router.route('/project/:_id', {
  name: 'projectPage',
  template: 'project',
  data: function(){
    var currentProject = this.params._id;
    var currentUser = Meteor.userId();
    return Projects.findOne({ _id: currentProject, user: currentUser });
  },
  waitOn: function(){
    var currentUserId = Meteor.userId();
    return [Meteor.subscribe("projects", currentUserId), Meteor.subscribe("folders", currentUserId), Meteor.subscribe("posts", currentUserId)];
  }
});

//where all user projects are displayed
Router.route('/profile/:_id', {
  name: 'profilePage',
  template: 'profile',
  notFoundTemplate: 'notFound',
  data: function(){
    var currentUser = Meteor.userId();
    return Meteor.users.findOne();
  },
  waitOn: function(){
    var currentUserId = Meteor.userId();
    return [Meteor.subscribe("projects", currentUserId), Meteor.subscribe("folders", currentUserId), Meteor.subscribe("posts", currentUserId)];
  }
});

Router.route('/folder/:_project/:_id', {
  name: 'folderPage',
  template: 'folder',
  notFoundTemplate: 'notFound',
  action : function () {
    if (this.ready()) this.render();
  },
  waitOn: function(){
    var currentUserId = Meteor.userId();
    return [Meteor.subscribe("projects", currentUserId), Meteor.subscribe("folders", currentUserId), Meteor.subscribe("posts", currentUserId)];
  },
  data: function(){
    var currentFolder = this.params._id;
    var currentUser = Meteor.userId();
    return currentFolder;
  },
});


  AccountsTemplates.configure({
    defaultLayout: 'layout',
  });

  Router.route('/', {
    name: 'home',
    template: 'home'
  });

  Router.route('/about',{
    name: 'about',
    template: 'aboutus'
  });

  AccountsTemplates.configureRoute('signIn', {
    redirect: function(){
      var user = Meteor.user();
      if (user)
      Router.go('/profile/' + user._id);
    }
  });

  //Routes
  AccountsTemplates.configureRoute('changePwd');
  AccountsTemplates.configureRoute('enrollAccount');
  AccountsTemplates.configureRoute('forgotPwd');
  AccountsTemplates.configureRoute('resetPwd');
  AccountsTemplates.configureRoute('signUp',{
    redirect: function(){
      var user = Meteor.user();
      if (user)
      Router.go('/profile/' + user._id);
    }
    });
  AccountsTemplates.configureRoute('verifyEmail');
