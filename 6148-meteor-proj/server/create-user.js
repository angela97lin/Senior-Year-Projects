Accounts.onCreateUser(function(options, user) {
  user.projects = [];
  if (options.profile) {
    user.profile = options.profile;
  }
  if (options.email) {
    user.email = options.email;
  }
  return user;
});
