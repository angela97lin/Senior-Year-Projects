/*
Projects: the projects Mongo collection stores
all projects from all users. Can be traversed by finding
via unique userIds. */

Projects = new Mongo.Collection('projects');

/*
Folders: the folders under each project. Can be traversed by finding
via projectIds */

Folders = new Mongo.Collection('folders');
Posts = new Mongo.Collection('posts');
