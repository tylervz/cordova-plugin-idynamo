
Pod::Spec.new do |s|
  s.name             = 'MTSCRA'
  s.version          = '1.0.0'
  s.summary          = 'MagTek MTSCRA SDK'
  s.homepage         = 'https://www.magtek.com'
  s.license          = { :type => 'Commercial' }
  s.author           = { 'MagTek' => 'support@magtek.com' }
  s.source           = { :path => '.' }

  s.ios.deployment_target = '12.0'

  s.vendored_frameworks = 'MTSCRA.xcframework'

  s.frameworks = 'AVFoundation', 'ExternalAccessory', 'AudioToolbox', 'AudioUnit', 'CoreAudioTypes'

  s.pod_target_xcconfig = {
    'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386',
    'VALID_ARCHS' => 'arm64 x86_64'
  }
end
