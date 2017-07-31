const gulp = require('gulp');
const sass = require('gulp-sass');
const fileinclude = require('gulp-file-include');
const compress = require('gulp-compress');
const minify = require('gulp-minify');
const browserify = require('gulp-browserify');
const imagemin = require('gulp-imagemin');

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
  gulp.watch('img/*',['imgmin']);
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
gulp.task('imgmin', function() {
    gulp.src('img/*')
        .pipe(imagemin([
			imagemin.jpegtran({progressive: true})
		]))
        .pipe(gulp.dest('dist/images'))
});
