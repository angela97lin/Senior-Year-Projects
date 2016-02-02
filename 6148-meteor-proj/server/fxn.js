Meteor.methods({
  'createProj': function(currentUserId, projName, projDesc){
    projectId = Projects.insert({user: currentUserId, projName: projName, projDesc: projDesc, folders: [], posts:[] });
    Meteor.users.update({_id:currentUserId}, {$addToSet:{projects:projectId}});
  },
  'createFolder': function(currentUserId, projectId, folderName, folderDesc){
    folderId = Folders.insert({user: currentUserId, proj: projectId, folderName: folderName, folderDesc: folderDesc, posts: []});
    Projects.update({_id:projectId}, {$addToSet:{folders:folderId}});
  },
  'createPost': function(currentUserId, projId, folderId, postName, postDesc, postImg){
    postId = Posts.insert({user: currentUserId, proj: projId, folder: folderId, postName: postName, postDesc: postDesc, postImg: postImg});
    Folders.update({_id:folderId}, {$addToSet:{posts:postId}});
  },
  'updateProj': function(currentProjId, updatedProjName, updatedProjDesc){
    projectId = Projects.update({_id: currentProjId}, {$set:{projName: updatedProjName, projDesc: updatedProjDesc}});
  },
  'updatePost': function(currentPostId, updatedPostName, updatedPostDesc, updatedPostImg){
    postId = Posts.update({_id: currentPostId}, {$set:{postName: updatedPostName, postDesc: updatedPostDesc, postImg: updatedPostImg}});
  },
  'updateFolder': function(currentFolderId, updatedFolderName, updatedFolderDesc){
    folderId = Folders.update({_id: currentFolderId}, {$set:{folderName: updatedFolderName, folderDesc: updatedFolderDesc}});
  },
  'deletePost': function(currentPostId, currentFolderId){
    folderId = Folders.update({_id: currentFolderId}, {$pull:{posts: currentPostId}});
    Posts.remove({_id: currentPostId});
  },
  'deleteFolder': function(currentUserId, currentProjId, currentFolderId){
    Posts.remove({folder:currentFolderId});
    Projects.update({_id: currentProjId}, {$pull:{folders: currentFolderId}});
    Folders.remove({_id: currentFolderId});
  },
  'deleteProject': function(currentUserId, currentProjId){
    Posts.remove({proj:currentProjId});
    Folders.remove({proj: currentProjId});
    Projects.remove({_id: currentProjId});
    Meteor.users.update({_id:currentUserId}, {$pull:{projects:currentProjId}});
  },
});


Meteor.publish("projects", function (currentUserId) {
  return Projects.find({user:currentUserId});
});

Meteor.publish("folders", function (currentUserId) {
  return Folders.find({user:currentUserId});
});

Meteor.publish("posts", function (currentUserId) {
  return Posts.find({user:currentUserId});
});
