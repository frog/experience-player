

require 'fileutils'

desc "last steps required to build a project"
task :setup do
  sh "git submodule update --init --recursive"
  FileUtils.rm_rf "frog-log/libraries/cpp/cpr/build"
  FileUtils.cd("frog-log/libraries/cpp/cpr/") do
    FileUtils.mkdir("build")
      FileUtils.cd("build") do
        sh "cmake .."
        sh "make"
      end
  end
end
