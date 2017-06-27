var gulp = require('gulp');
var sass = require('gulp-sass');
var fileinclude = require('gulp-file-include');
var compress = require('gulp-compress');
var minify = require('gulp-minify');
var browserify = require('gulp-browserify');

gulp.task('styles', function() {
    gulp.src('sass/application.scss')
        .pipe(sass().on('error', sass.logError))
        .pipe(gulp.dest('./build/css/'));
});
gulp.task('fileinclude', function() {
  gulp.src(['index.html'])
    .pipe(fileinclude({
      prefix: '@@',
      basepath: '@file'
    }))
    .pipe(gulp.dest('./build'));
});
gulp.task('default',function(){
  gulp.watch('sass/**/*.scss',['styles']);
  gulp.watch('*.html',['fileinclude']);
  gulp.watch('js/*.js',['scripts']);
  gulp.watch('js/*.js',['compress']);
});
gulp.task('compress', function () {
  gulp.src('./build/js/*.js')
  .pipe(minify({
      ext:{
          src:'-debug.js',
          min:'.js'
      },
      exclude: ['tasks'],
      ignoreFiles: ['.combo.js', '-min.js']
  }))
  .pipe(gulp.dest('./build/js/'))
});
gulp.task('scripts', function() { 
    gulp.src('js/nodemailer.js')
      .pipe(browserify({
        insertGlobals : true,
        debug : !gulp.env.production
      }))
  .pipe(gulp.dest('./build/js'))
});
