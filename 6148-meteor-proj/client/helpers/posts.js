Template.post.helpers({
  'post': function(){
    var currentUserId = Meteor.userId();
    console.log(this[0]);
    var folderId = this[0];
    var postId = this[1].toString();
    var post = Posts.find().fetch();
    if (post)
    console.log(post);
    return Posts.find({_id: postId}).fetch();
  }

});

Template.post.onRendered(function () {
  this.$('.image').dimmer({
    on: 'hover'
  });
});

Template.post.events({
  'click .deletelink': function(e, t){
    MaterializeModal.confirm({
      title: "Delete post?",
      post_info: t.data,
      label: "Delete Post!",
      message: "Do you want to delete this post? This cannot be undone.",
      callback: function(error, response) {
        if (response.submit) {
          var currentFolderId = t.data.folder;
          var currentPostId = t.data._id;
          Meteor.call('deletePost', currentPostId, currentFolderId, function(error, result){
            if (error){
              console.log(error.reason);
            } else {
              console.log("Sucess in deleting post!");
            }
          })
          //Materialize.toast("Yes!", 5000, "green");
        } else {
          //Materialize.toast("No!", 5000, "red");
        }
      }
    });
  },
  'click .ui.inverted.button.modbut': function(e, t){
    e.preventDefault();
    MaterializeModal.form({
      title: "Edit your post:",
      bodyTemplate: "edit-post-form",
      post_info: t.data,
      closeLabel: "Cancel",
      submitLabel: "Update Post!",
      callback: function(error, response) {
        if (response.submit) {
          var updatedPostName = response.form.updatePostName;
          var updatedPostDesc = response.form.updatePostDesc;
          var updatedPostImg = response.form.updatePostImg;
          var currentPostId = t.data._id;
          Meteor.call('updatePost', currentPostId, updatedPostName, updatedPostDesc, updatedPostImg, function(error, result){
            if (error){
              console.log(error.reason);
            } else {
              console.log("Sucess in updating post!");
            }
          });
          //for (var field in response.form) {
          //Materialize.toast(field + ": " + response.form[field], 5000, "green");
          //}
        } else {
          //Materialize.toast("Cancelled by user!", 5000, "red");
        }
      }
    });
  }
});
