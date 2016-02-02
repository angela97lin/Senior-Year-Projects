
Template.profile.helpers({
  'projects': function(){
    var currentUserId = Meteor.userId();
    return Projects.find({user:currentUserId}, {sort:{projName: 1}});
  },
  'user': function(){
    var currentUserId = Meteor.userId();
    return currentUserId;
  }
});

Template.profile.events({
  'click .deletelink': function(e, t){
    var self = this;
    MaterializeModal.confirm({
      title: "Delete project?",
      self: self,
      label: "Delete Project!",
      message: "Do you want to delete this project? This will delete everything under this project and CANNOT be undone.",
      callback: function(error, response) {
        if (response.submit) {
          var currentUserId = Meteor.userId();
          var currentProjId = self._id;
          Meteor.call('deleteProject', currentUserId, currentProjId, function(error, result){
            if (error){
              console.log(error.reason);
            } else {
              console.log("Sucess in deleting project!");
            }
          })
          //Materialize.toast("Yes!", 5000, "green");
        } else {
          //Materialize.toast("No!", 5000, "red");
        }
      }
    });
  },
  "submit .new-proj": function(event){
    //prevents reloading
    event.preventDefault();
    var currentUserId = Meteor.userId();
    var projName = event.target.projname.value;
    var projDesc = event.target.projdes.value;
    if (projName === ""){
      console.log("Empty");
      FlashMessages.sendError("Project name required!");
    }
    else{
      Meteor.call('createProj', currentUserId, projName, projDesc, function(error, result){
        if (error){
          console.log(error.reason);
        } else {
          //console.log("Sucess!");
          //var projectId = result;
        }
      });
    }
  },
  'click .ui.button.editproj': function(e, t){
    e.preventDefault();
    var self = this;
    MaterializeModal.form({
      title: "Edit your project:",
      bodyTemplate: "edit-proj-form",
      closeLabel: "Cancel",
      submitLabel: "Update Project!",
      self: self,
      callback: function(error, response) {
        if (response.submit) {
          var currentProjId = self._id;
          var updatedProjName = response.form.updatedProjName;
          var updatedProjDesc = response.form.updatedProjDesc;
          if (updatedProjName === ""){
            FlashMessages.sendError("Project name required!");
          }
          else {
            Meteor.call('updateProj', currentProjId, updatedProjName, updatedProjDesc, function(error, result){
              if (error){
                console.log(error.reason);
              } else {
                console.log("Sucess in updating project!");
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
