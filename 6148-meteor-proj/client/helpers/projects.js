Template.project.helpers({
  'folders': function(){
    var currentUserId = Meteor.userId();
    var projectId = this._id;
    return Folders.find({proj:projectId}, {sort:{folderName: 1}});
  },
  'projectId': function(){
      var projectId = this.proj;
    return projectId;
  }
});

Template.project.events({
  'click .deletelink': function(e, t){
  var self = this;
  MaterializeModal.confirm({
    title: "Delete folder?",  
    self: self,
    label: "Delete Folder!",
    message: "Do you want to delete this folder? This will delete everything under this folder and CANNOT be undone.",
    callback: function(error, response) {
      if (response.submit) {
        var currentUserId = Meteor.userId();
        var currentProjId = self.proj;
        var currentFolderId = self._id;
        Meteor.call('deleteFolder', currentUserId, currentProjId, currentFolderId, function(error, result){
          if (error){
            console.log(error.reason);
          } else {
            console.log("Sucess in deleting folder!");
          }
        })
        //Materialize.toast("Yes!", 5000, "green");
      } else {
        //Materialize.toast("No!", 5000, "red");
      }
    }
  });
},
  "submit .new-folder": function(event){
    event.preventDefault();
    var currentUserId = Meteor.userId();
    var folderName = event.target.foldername.value;
    var folderDesc = event.target.folderdes.value;

    if (folderName === ""){
      FlashMessages.sendError("Folder name required!");
      FlashMessages.clear();
    }
    else {
      var projectId = this._id;
      Meteor.call('createFolder', currentUserId, projectId, folderName, folderDesc, function(error, result){
        if (error){
          console.log(error.reason);
        } else {
          console.log("Sucess!");
        }
      });
    }
  },
  'click .ui.button.editfolder': function(e, t){
    e.preventDefault();
    var self = this;
    MaterializeModal.form({
      title: "Edit your folder:",
      bodyTemplate: "edit-folder-form",
      closeLabel: "Cancel",
      submitLabel: "Update Folder!",
      self: self,
      callback: function(error, response) {
        if (response.submit) {
          var currentFolderId = self._id;
          var updatedFolderName = response.form.updatedFolderName;
          var updatedFolderDesc = response.form.updatedFolderDesc;
          if (updatedFolderName === ""){
            FlashMessages.sendError("Folder name required!");
          }
          else {
            Meteor.call('updateFolder', currentFolderId, updatedFolderName, updatedFolderDesc, function(error, result){
              if (error){
                console.log(error.reason);
              } else {
                console.log("Sucess in updating folder!");
              }
            });
            // (var field in response.form) {
            //Materialize.toast(field + ": " + response.form[field], 5000, "green");
            //}
          }
        } else {
          //Materialize.toast("Cancelled by user!", 5000, "red");
        }
      }
    });
  }
});
