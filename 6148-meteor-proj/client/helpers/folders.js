Template.folder.helpers({
  'posts': function(){
    var currentUserId = Meteor.userId();
    var folderId = this.toString();
    return Posts.find({folder:folderId}, {sort:{postName: 1}});
  },
  'folder': function(){
    var folderId = this.toString();
    var folder = Folders.findOne({_id:folderId});
    Template.instance().folder = folder;
    return folder;
  },
  'project': function(projectId){
    return Projects.find({_id:projectId});
  },
  'projects': function(){
    var currentUserId = Meteor.userId();
    return Projects.find({user:currentUserId}, {sort:{projName: 1}});
  },
  'folders': function(projectId){
    //find other folders within given project
    var folders = Folders.find({proj:projectId});
    return folders;
  }
});

Template.folder.onRendered(function(){
  this.$('.image').dimmer({
    on: 'hover'
  });
  this.$('.ui.dropdown').dropdown();
});

Template.folder.events({
  "submit .new-post": function(event){
    //prevents reloading
    event.preventDefault();
    var currentUserId = Meteor.userId();
    var postName = event.target.postname.value;
    var postDesc = event.target.postdes.value;
    var postImg = event.target.postimg.value;
    var projectId = Template.instance().folder.proj;
    var folderId = this.toString();
    if (postDesc === ""){
      FlashMessages.sendError("Post description required!");
    }
    else if (postImg === ""){
      FlashMessages.sendError("Post image required!");
    }
    else {
      Meteor.call('createPost', currentUserId, projectId, folderId, postName, postDesc, postImg, function(error, result){
        if (error){
          console.log(error.reason);
        } else {
          console.log("Sucess in creating and inserting post!");
        }
      });
    }
  }
});
